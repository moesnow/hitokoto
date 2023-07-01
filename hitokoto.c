#include <curl/curl.h>
#include <json-c/json.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define API_URL "https://v1.hitokoto.cn"

size_t write_callback(void *contents, size_t size, size_t nmemb, char **output) {
    size_t total_size = size * nmemb;
    *output = realloc(*output, total_size + 1);
    if (*output == NULL) {
        fprintf(stderr, "Failed to allocate memory.\n");
        return 0;
    }
    memcpy(*output, contents, total_size);
    (*output)[total_size] = '\0';
    return total_size;
}

int main() {
    CURL *curl;
    CURLcode res;
    char *response = NULL;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, API_URL);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            // 解析 JSON 数据
            json_object *json = json_tokener_parse(response);
            if (json == NULL) {
                fprintf(stderr, "Failed to parse JSON data.\n");
            } else {
                // 获取句子内容
                json_object *sentence;
                json_object *from;
                if (json_object_object_get_ex(json, "hitokoto", &sentence) && json_object_object_get_ex(json, "from", &from)) {
                    printf(
                        "\033[33m"
                        "%s"
                        "\033[30m"
                        ": “"
                        "\033[38;5;165m"
                        "%s"
                        "\033[30m"
                        "”"
                        "\n",
                        json_object_get_string(from), json_object_get_string(sentence));
                } else {
                    fprintf(stderr, "Failed to retrieve sentence from JSON data.\n");
                }
                json_object_put(json);
            }
        }
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

    free(response);
    return 0;
}
