#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata)
{
  size_t total_size = size * nmemb;
  fwrite(ptr, size, nmemb, stdout);
  return total_size;

}

int main(int argc, char *argv[])
{
  CURL *curl;
  CURLcode res;
  curl = curl_easy_init();

  if (!curl)
  {
    fprintf(stderr, "Failed to initialize curl\n");
    return EXIT_FAILURE;
  }

  curl_version_info_data *ver = curl_version_info(CURLVERSION_NOW);
  printf("libcurl version %u.%u.%u\n",
       (ver->version_num >> 16) & 0xff,
       (ver->version_num >> 8) & 0xff,
       ver->version_num & 0xff);

  curl_easy_setopt(curl, CURLOPT_URL, "localhost:8080/files/hello");
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
  res = curl_easy_perform(curl);
  if (res != CURLE_OK)
  {
    fprintf(stderr, "curl_easy_perform() failed %s\n", curl_easy_strerror(res));
    return EXIT_FAILURE;
  }

  curl_easy_cleanup(curl);
  return EXIT_SUCCESS;
}
