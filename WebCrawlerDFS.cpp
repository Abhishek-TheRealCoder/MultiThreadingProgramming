#include<iostream>
#include<bits/stdc++.h>
#include<thread>
#include<mutex>

using namespace std;

class HtmlParser
{
    public:
    vector<string> getUrls(string url)
    {
        vector<string> urls;
        if(url == "google.com")
        {
            urls.push_back("facebook.com");
            urls.push_back("twitter.com");
        }
        else if(url == "facebook.com")
        {
            urls.push_back("linkedin.com");
            urls.push_back("instagram.com");
            urls.push_back("google.com");
            urls.push_back("chatgpt.com");
        }
        return urls;
    }
};

class MultiThreadedWebCrawler
{
    unordered_map<string,int> visited;  
    std::mutex mtx;
    
    public:

    void executeDfs(string url, HtmlParser* htmlParser)
    {
        unique_lock<mutex> lock(mtx);
        if(visited[url])
        {
            return ;
        }

        visited[url] = 1;
        cout<< "Crawling URL: " << url << endl;

        lock.unlock();

        vector<string> urls = htmlParser->getUrls(url);
        vector<thread> threads; // for n number of urls in the worst case we can have n number of threads to crawl those urls in parallel

        for(auto node : urls)
        { 
            if(visited[node] != 1)
            {
                threads.emplace_back(thread(&MultiThreadedWebCrawler::executeDfs, this, node, htmlParser));
            }
        }

        for(int i = 0;i < threads.size();i++)
        {
            threads[i].join();
        }
        return ;
    }

};

int main()
{
    MultiThreadedWebCrawler* crawler = new MultiThreadedWebCrawler();
    HtmlParser* htmlParser = new HtmlParser();
    crawler->executeDfs("google.com", htmlParser);
    return 0;
}