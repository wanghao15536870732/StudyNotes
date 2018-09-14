import requests
from urllib.error import URLError
import os
import urllib.request
from lxml import etree
import logging

logging.basicConfig( level= logging.INFO , format= '%(asctime)s-%(message)s')
logger = logging.getLogger( __name__ )

headers = {'Accept': '*/*',
           'Accept-Language': 'en-US,en;q=0.8',
           'Cache-Control': 'max-age=0',
           'User-Agent': 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/48.0.2564.116 Safari/537.36',
           'Connection': 'keep-alive'
           }

def getHTML(url):
    try:
        r = requests.get( url )
        if r.status_code == 200 :
            return r.text
        else:
            print( "error code : " + r.status_code  )
    except:
        print( "error:" + requests.get( url ).status_code )

def getMoviesUrls( url ):
    s = etree.HTML( getHTML( url ) )
    movies = s.xpath( '//div[@class="pic"]//a/@href')
    return movies

def getImgUrls ( url ):
    s = etree.HTML( getHTML( url ) )
    imgs = s.xpath ( '//li//a//img/@src' )
    return imgs

def getvideo( url ) :
    s = etree.HTML( getHTML( url ) )
    video = s.xpath( '//a[@class="related-pic-video"]/@href')[0]
    s = etree.HTML( getHTML( video ) )
    video = s.xpath( '//video//source/@src')[0]
    return video

def getInfo( url ) :
    s = etree.HTML( getHTML( url ) )
    name = s.xpath( '//span[@property="v:itemreviewed"]/text()')[0]
    logging.info( '正在获取:' + name + '\t' + url )
    director = s.xpath( '//span//a[@rel="v:directedBy"]/text()') #导演名
    score = s.xpath( '//strong[@property="v:average"]/text()')
    actor = s.xpath ( '//span[@class="actor"]//a[@rel="v:starring"]/text()')[0:5]#前五个主演
    kind = s.xpath ( '//span[@property="v:genre"]/text()')
    comment = s.xpath ( '//div[@class="comment"]//p/text()')
    summary = s.xpath ( '//span[@property="v:summary"]/text()')
    final_summary = []
    final_comment = []
    for i in summary :
        s = str(i).strip()
        final_summary.append( s )
    for i in comment :
        s= str ( i ).strip()
        s = s + '\n'
        final_comment.append( s )
    info = {
        '片名': name ,
        '导演': director ,
        '评分': score ,
        '主演': actor ,
        '类型': kind ,
        '简介': final_summary ,
        '简评': final_comment
    }
    return info

def download( path , url , name , str ):
        logging.info( msg= "正在下载:" + url )
        filename = os.path.join( path , name + str )
        try:
            urllib.request.urlretrieve( url , filename )
        except URLError as e :
            logging.error( "download field" )

def write( path , info ):
    path = path + '//' + info + '.txt'
    file = open( path , 'w' )
    for i in info :
        file.write( i + ':' )
        for j in info[i] :
            file.write( str( j )  )
        file.write( '\n' )
    file.close()

def setPath( name ):
    path = os.path.join( "D://Test/" , name )
    os.mkdir( path )
    return path

if __name__ == '__main__' :
    for i in range ( 0 , 250 , 25 ) :
        url = r"https://movie.douban.com/top250?start=" + str(i) + r"&filter="
        movieList = getMoviesUrls( url )
        for movie in movieList :
            imgList = getImgUrls( movie )
            video = getvideo( movie )
            info = getInfo( movie )
            path = setPath( info['片名'] )
            index = 1
            for img in imgList :
                download(name=info['片名']+'剧照'+str(index), path=path, url= img , str='.jpg' )
                index += 1
            download( name=info['片名']+'视频' , path=path , url= video , str='.mp4' )
            write( path , info )