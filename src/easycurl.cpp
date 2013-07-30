////////////////////////////////////
//////
// EasyMode for libcurl
// now using libcurl sucks less :-)
/////
////////////////////////////////////

#include "easycurl.h"
#include "stripper.h"

bool EasyCurl::is_not_printable(char c) {
  //locale l(ISPRINT_LOCALE);
  //return !isprint(c, l);
  return !((unsigned int)c > 31);
}

string EasyCurl::filterUnprintables(string str)
{
  str.erase(remove_if(str.begin(), str.end(), EasyCurl::is_not_printable), str.end());
  return str;
}

string EasyCurl::translateHtmlEntities(string str) {
  char buff[str.length()+1];
  decode_html_entities_utf8(buff, str.c_str());
  return string(buff);
}

int EasyCurl::headerWriter(char *data, size_t size, size_t nmemb, EasyCurl* instance) {
  return instance->instanceHeaderWriter(data, size, nmemb);
}

int EasyCurl::instanceHeaderWriter(char *data, size_t size, size_t nmemb) {
  if (!memcmp(data, "\r\n", std::min(size*nmemb, 2U))) {
    if (extractContentType() && !isHtml) {
      // early abort if not html
      return 0;
    }
  }

  //Stop if max size exceeded
  this->bufferTotal += size * nmemb;
  if (this->bufferTotal > DOWNLOAD_SIZE) {
    return 0;
  }

  return size * nmemb;
}

int EasyCurl::bodyWriter(char *data, size_t size, size_t nmemb, EasyCurl* instance) {
  return instance->instanceBodyWriter(data, size, nmemb);
}

int EasyCurl::instanceBodyWriter(char *data, size_t size, size_t nmemb) {
  // Append the data to the buffer
  this->response_body.append(data, size * nmemb);

  //Stop if max size exceeded
  this->bufferTotal += size * nmemb;
  if (this->bufferTotal > DOWNLOAD_SIZE) {
    return 0;
  }

  return size * nmemb;
}

bool EasyCurl::extractContentType() {
  char *content_type;
  long response;

  curl_easy_getinfo(this->curl, CURLINFO_RESPONSE_CODE, &response);
  if (response == 301 || response == 302) {
    return false;
  }

  curl_easy_getinfo(this->curl, CURLINFO_CONTENT_TYPE, &content_type);
  if (content_type == NULL) {
    return false;
  }

  this->response_content_type = filterUnprintables(content_type);
  this->isHtml = determineIfHtml();
  return true;
}

bool EasyCurl::determineIfHtml() {
  static string valid[] = {"text/html", "application/xhtml+xml"};

  for (int i = 0; i < 2; i++) {
    if (this->response_content_type.compare(0, valid[i].length(), valid[i]) == 0) {
      return true;
    }
  }
  return false;
}

string EasyCurl::parseFor(string buffer, string expr, int match_no) {
  boost::regex re;
  boost::cmatch matches;
  re.assign(expr, boost::regex_constants::icase);

  // Throws exceptions
  if (boost::regex_match(buffer.c_str(), matches, re, boost::match_not_eol)) {
    return filterUnprintables(matches[match_no]);
  } else {
    return "";
  }
}

EasyCurl::EasyCurl(string url) {
  this->requestWentOk = true;
  this->request_url = url;
  int result;

  result = this->curlSetup();
  if (result < 0) {
    this->requestWentOk = false;
    return;
  }

  result = this->curlRequest();
  if (result < 0) {
    this->requestWentOk = false;
    this->error_message = curl_easy_strerror(this->curlCode);
    return;
  }

  extractMetadata();
  // Obtain HTML Title + translate HTML Entities
  extractTitle();
}

EasyCurl::~EasyCurl() {
  if (this->curl) {
    curl_easy_cleanup(this->curl);
  }
}

bool EasyCurl::extractTitle() {
  if (this->isHtml) {
    try {
      this->html_title = EasyCurl::parseFor(this->response_body,
          ".*(<title>|<title .+>)(.*)</title>.*", 2);
    } catch(...) {
      this->requestWentOk = false;
    }
  }

  if (this->html_title == "") {
    this->html_title = "N/A";
  } else {
    //strip leading and trailing whitespace
    if (this->requestWentOk) {
      this->html_title = stripWhitespace(EasyCurl::translateHtmlEntities(this->html_title));
    }
  }

  return this->requestWentOk;
}

int EasyCurl::curlSetup() {
  // Write all expected data in here
  this->curl = curl_easy_init();

  this->bufferTotal = 0;

  if (!curl)
    return -1;

  curl_easy_setopt(this->curl, CURLOPT_URL, this->request_url.c_str());
  curl_easy_setopt(this->curl, CURLOPT_USERAGENT, USERAGENT_STR);

  //I'm not sure how CURL_TIMEOUT works
  curl_easy_setopt(this->curl, CURLOPT_TIMEOUT, 10);
  curl_easy_setopt(this->curl, CURLOPT_MAXREDIRS, 10);
  curl_easy_setopt(this->curl, CURLOPT_HEADER, 0);
  curl_easy_setopt(this->curl, CURLOPT_NOSIGNAL, 1);
  curl_easy_setopt(this->curl, CURLOPT_ENCODING, "identity");
  curl_easy_setopt(this->curl, CURLOPT_FOLLOWLOCATION, 1);

  curl_easy_setopt(this->curl, CURLOPT_WRITEDATA, (void*)this);
  curl_easy_setopt(this->curl, CURLOPT_WRITEFUNCTION, EasyCurl::bodyWriter);

  curl_easy_setopt(this->curl, CURLOPT_HEADERDATA, (void*)this);
  curl_easy_setopt(this->curl, CURLOPT_HEADERFUNCTION, EasyCurl::headerWriter);

  return 0;
}

int EasyCurl::curlRequest() {
  // Attempt to retrieve the remote page
  this->curlCode = curl_easy_perform(this->curl);

  if ((this->curlCode != CURLE_OK) && (this->curlCode != CURLE_WRITE_ERROR)) {
    return -1;
  }

  return 0;
}

bool EasyCurl::extractMetadata() {
  char* effective_url;
  double content_length;
  long response_code;
  long redirect_count;

  // Along with the request get some information
  curl_easy_getinfo(this->curl, CURLINFO_EFFECTIVE_URL, &effective_url);
  curl_easy_getinfo(this->curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &content_length);
  curl_easy_getinfo(this->curl, CURLINFO_RESPONSE_CODE, &response_code);
  curl_easy_getinfo(this->curl, CURLINFO_REDIRECT_COUNT, &redirect_count);

  ostringstream oss;
  oss.precision(20);

  this->request_url = effective_url;

  oss << content_length;
  this->response_content_length = oss.str();
  oss.str("");

  oss << response_code;
  this->response_code = oss.str();
  oss.str("");

  oss << redirect_count;
  this->redirect_count = oss.str();
  oss.str("");

  return true;
}
