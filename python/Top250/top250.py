import urllib

import requests
from bs4 import BeautifulSoup
import re
import random

# 读取文档
def read(path):
    with open(path, 'r', encoding='utf-8') as f:
        txt = []
        for s in f.readlines():
            txt.append(s.strip())
    return txt

# 写入文档
def write(path,text):
    with open(path,'a', encoding='utf-8') as f:
        f.writelines(text)
        f.write('\n')

# 获得指定起始排名的电影url
def get_url(root_url,start):
    return root_url + "?start=" + str(start) + "&filter="

# # 获取免费ip代理池
# def get_ip_list(url):
#     web_data = requests.get(url)
#     print(web_data.text)
#     soup = BeautifulSoup(web_data.text,'lxml')
#     ips = soup.find_all('tr')
#     ip_list = []
#     for i in range(1,len(ips)):
#         ip_info = ips[i]
#         tds = ip_info.find_all('td')
#         ip_list.append(tds[1].text + tds[2].text)
#     print(ip_list)
#     # 检测ip可用性，移除不可用ip
#     for ip in ip_list:
#         try:
#             proxy_host = "https://" + ip
#             proxy_temp = {"https": proxy_host}
#             res = urllib.urlopen(url,proxy_temp).read()
#         except Exception as e:
#             ip_list.remove(ip)
#             continue
#     return ip_list
#
# # 从ip池中随机获取ip列表
# def get_random_ip(ip_list):
#     proxy_list = []
#     for ip in ip_list:
#         proxy_list.append('https://' + ip)
#     proxy_ip = random.choice(proxy_list)
#     proxies = {'https': proxy_ip}
#     return proxies
#
# # 获取网页内容
# def get_html_text(ip_url,proxies):
#     try:
#         r = requests.get(ip_url,proxies)
#         r.raise_for_status()
#         r.encoding = r.apparent_encoding
#     except:
#         return 0
#     else:
#         return r.text

# 根据传入的url,获取电影排名及评分,
def get_review(page_url):
    # 存放电影信息的列表
    movies_list = []
    # 请求url,返回response对象
    path = 'ip.txt'
    # ips = read(path)  # 读取爬到的ip数量
    # print(random.choice(ips))
    # response = requests.get(page_url, proxies=random.choice(ips))
    response = requests.get(page_url)
    # print(response.text)
    # 指定lxml解析器解析html文档
    soup = BeautifulSoup(response.text,"lxml")
    # 获取包含所有电影信息的节点
    soup = soup.find('ol','grid_view')

    for tag_i in soup.find_all('li'):
        dict = {}
        # 排名
        dict['rank'] = tag_i.find("em").string
        # 电影名字
        dict['name'] = tag_i.find_all("span","title")[0].string
        # 电影封面url
        dict['url'] = tag_i.find("img")['src']
        # 电影评分
        dict['score'] = tag_i.find("span","rating_num").string
        # 共有多少人评价
        dict['num_comment'] = tag_i.find("div","star").find_all("span")[3].string
        # 电影短评
        if(tag_i.find("span","inq")):
            dict['comment'] = tag_i.find("span","inq").string
        # 电影导演跟演员
        # 这段信息中有太多非法符号你需要替换掉
        content_list = tag_i.find("div","bd").find("p","").get_text().replace(" ","").replace("\n","")
        content_list = content_list.replace("\xa0", "").replace("\xee", "").replace("\xf6", "").\
            replace("\u0161", "").replace("\xf4", "").replace("\xfb", "").replace("\u2027", "").replace("\xe5", "")
        dict['director'] = content_list.split("导演:")[1].split("主演")[0]

        print(content_list.split("导演:")[1].split("主演")[1].split)
        movies_list.append(dict)

    return movies_list

def beginScripy(s,path):
    root_url = 'https://movie.douban.com/top250'
    start = s
    while(start < 250):
        movie_list = get_review(get_url(root_url,start))
        # print(get_url(root_url,start))
        for movie_dict in movie_list:
            print('电影排名：' + movie_dict['rank'])
            print('电影名字：' + movie_dict.get('name'))
            print('电影导演：' + movie_dict.get('director'))
            print('电影评分：' + movie_dict.get('score'))
            print('电影封面url：' + movie_dict.get('url'))
            print('共有' + movie_dict.get('num_comment'))
            print('电影短评：' + movie_dict.get('comment','无评词'))
            print('------------------------------------------------------')

            write(path,'电影排名：' + movie_dict['rank'])
            write(path,'电影名字：' + movie_dict.get('name'))
            write(path,'电影导演：' + movie_dict.get('director'))
            write(path,'电影评分：' + movie_dict.get('score'))
            write(path,'电影封面url：' + movie_dict.get('url'))
            write(path,'共有' + movie_dict.get('num_comment'))
            write(path,'电影短评：' + movie_dict.get('comment','无评词'))
            write(path,'------------------------------------------------------')

        start += 25

if __name__ == '__main__':
    path = 'doubanTop250.txt'
    beginScripy(225,path)