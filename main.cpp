#include <iostream>
#include <string>
#include <fstream>
#include <curl/curl.h>
using namespace std;

size_t curl_callback(void *ptr, size_t size, size_t nmemb, string* data) {
    data->append((char*)ptr, size * nmemb);
    return size * nmemb;
}

int main(int argc, char* argv[]) {
    CURL *curl;
    CURLcode res;
    
    string city = "London";
    if(argc != 1 && string(argv[1])[0] != '-') {
        city = argv[1];
    }
    else {
        ifstream file("city.txt");
        file >> city;
    }

    curl = curl_easy_init();
    if(curl) {
        string response_string, URL = "https://api.weatherapi.com/v1/current.json?key=c25ec9e21f534c90abd100024232805&q=" + city + "&aqi=no";

        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "User-Agent: libcurl-agent/1.0");
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "Cache-Control: no-cache");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
        curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            cout << "Error: " << res << '\n';
            curl_easy_cleanup(curl);
            return 1;
        }

        if(response_string.size() == 63) {
            cout << "Enter a valid city\n";
            curl_easy_cleanup(curl);
            return 1;
        }

        bool remember = false, celsius = true;
        for(int i = 1; i < argc; i++) {
            if(string(argv[i]) == "-r") remember = true;
            else if(string(argv[i]) == "-f") celsius = false;
        }

        int ind = 7;
        if(celsius) {
            while(response_string[ind - 8] != 't' || response_string[ind - 7] != 'e' || response_string[ind - 6] != 'm' || response_string[ind - 5] != 'p' || response_string[ind - 4] != '_' || response_string[ind - 3] != 'c') ind++;
        }
        else {
            while(response_string[ind - 8] != 't' || response_string[ind - 7] != 'e' || response_string[ind - 6] != 'm' || response_string[ind - 5] != 'p' || response_string[ind - 4] != '_' || response_string[ind - 3] != 'f') ind++;
        }
        string temp = "";
        while(response_string[ind] != ',') {
            temp += response_string[ind];
            ind++;
        }

        if(remember) {
            system(("echo " + city + " > city.txt").c_str());
        }
        if(celsius) {
            cout << "It is currently " << temp << " °C in " << city << '\n';
        }
        else {
            cout << "It is currently " << temp << " °F in " << city << '\n';
        }
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }
    return 0;
}