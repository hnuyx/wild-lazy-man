# -*- coding: UTF-8 -*-
import json,random
import requests
import time,csv
from lxml import etree
from  pymysql import  *
# from save_to_mysql.demo import save_mysql
import os
import redis
import hashlib
from retrying import retry
#headers内容,网页上会有，其中cooies就包括登录的效果，暂时简单理解为：拉勾网不会因为我们的操作频繁而阻止

class LgPost(object):
    def __init__(self):
        self.headers = {
            # "Cookie": "user_trace_token=20171010163413-cb524ef6-ad95-11e7-85a7-525400f775ce; LGUID=20171010163413-cb52556e-ad95-11e7-85a7-525400f775ce; JSESSIONID=ABAAABAABEEAAJAA71D0768F83E77DA4F38A5772BDFF3E6; _gat=1; PRE_UTM=m_cf_cpt_baidu_pc; PRE_HOST=bzclk.baidu.com; PRE_SITE=http%3A%2F%2Fbzclk.baidu.com%2Fadrc.php%3Ft%3D06KL00c00f7Ghk60yUKm0FNkUsjkuPdu00000PW4pNb00000LCecjM.THL0oUhY1x60UWY4rj0knj03rNqbusK15yDLnWfkuWN-nj0sn103rHm0IHdDPbmzPjI7fHn3f1m3PDnsnH9anDFArH6LrHm3PHcYf6K95gTqFhdWpyfqn101n1csPHnsPausThqbpyfqnHm0uHdCIZwsT1CEQLILIz4_myIEIi4WUvYE5LNYUNq1ULNzmvRqUNqWu-qWTZwxmh7GuZNxTAn0mLFW5HDLP1Rv%26tpl%3Dtpl_10085_15730_11224%26l%3D1500117464%26attach%3Dlocation%253D%2526linkName%253D%2525E6%2525A0%252587%2525E9%2525A2%252598%2526linkText%253D%2525E3%252580%252590%2525E6%25258B%252589%2525E5%25258B%2525BE%2525E7%2525BD%252591%2525E3%252580%252591%2525E5%2525AE%252598%2525E7%2525BD%252591-%2525E4%2525B8%252593%2525E6%2525B3%2525A8%2525E4%2525BA%252592%2525E8%252581%252594%2525E7%2525BD%252591%2525E8%252581%25258C%2525E4%2525B8%25259A%2525E6%25259C%2525BA%2526xp%253Did%28%252522m6c247d9c%252522%29%25252FDIV%25255B1%25255D%25252FDIV%25255B1%25255D%25252FDIV%25255B1%25255D%25252FDIV%25255B1%25255D%25252FH2%25255B1%25255D%25252FA%25255B1%25255D%2526linkType%253D%2526checksum%253D220%26ie%3Dutf8%26f%3D8%26ch%3D2%26tn%3D98010089_dg%26wd%3D%25E6%258B%2589%25E5%258B%25BE%25E7%25BD%2591%26oq%3D%25E6%258B%2589%25E5%258B%25BE%25E7%25BD%2591%26rqlang%3Dcn%26oe%3Dutf8; PRE_LAND=https%3A%2F%2Fwww.lagou.com%2F%3Futm_source%3Dm_cf_cpt_baidu_pc; _putrc=347EB76F858577F7; login=true; unick=%E6%9D%8E%E5%87%AF%E6%97%8B; showExpriedIndex=1; showExpriedCompanyHome=1; showExpriedMyPublish=1; hasDeliver=63; TG-TRACK-CODE=index_search; _gid=GA1.2.1110077189.1507624453; _ga=GA1.2.1827851052.1507624453; LGSID=20171011082529-afc7b124-ae1a-11e7-87db-525400f775ce; LGRID=20171011082545-b94d70d5-ae1a-11e7-87db-525400f775ce; Hm_lvt_4233e74dff0ae5bd0a3d81c6ccf756e6=1507444213,1507624453,1507625209,1507681531; Hm_lpvt_4233e74dff0ae5bd0a3d81c6ccf756e6=1507681548; SEARCH_ID=e420ce4ae5a7496ca8acf3e7a5490dfc; index_location_city=%E5%8C%97%E4%BA%AC",
            "Cookie":"JSESSIONID=ABAAABAAADEAAFIF0390879C909ED6B25B79466EE283BE3; _ga=GA1.2.417433648.1513319104; _gid=GA1.2.1618013105.1513319104; Hm_lvt_4233e74dff0ae5bd0a3d81c6ccf756e6=1513319105; user_trace_token=20171215142351-84d77e04-e160-11e7-9a0b-525400f775ce; LGSID=20171215142351-84d782ed-e160-11e7-9a0b-525400f775ce; PRE_UTM=m_cf_cpt_baidu_pc; PRE_HOST=bzclk.baidu.com; PRE_SITE=http%3A%2F%2Fbzclk.baidu.com%2Fadrc.php%3Ft%3D06KL00c00f7Ghk60yUKm0FNkUs0dpWPp00000PW4pNb00000zJBmtg.THL0oUhY1x60UWdBmy-bIfK15yRvujDYnvf3nj0snADdrAm0IHYznDNAf1mdPbD3wjDvPjmkn1c3PHfsPYf3nRfsP16zw0K95gTqFhdWpyfqn101n1csPHnsPausThqbpyfqnHm0uHdCIZwsT1CEQLILIz4_myIEIi4WUvYE5LNYUNq1ULNzmvRqUNqWu-qWTZwxmh7GuZNxTAn0mLFW5HRLrjDL%26tpl%3Dtpl_10085_15730_11224%26l%3D1500117464%26attach%3Dlocation%253D%2526linkName%253D%2525E6%2525A0%252587%2525E9%2525A2%252598%2526linkText%253D%2525E3%252580%252590%2525E6%25258B%252589%2525E5%25258B%2525BE%2525E7%2525BD%252591%2525E3%252580%252591%2525E5%2525AE%252598%2525E7%2525BD%252591-%2525E4%2525B8%252593%2525E6%2525B3%2525A8%2525E4%2525BA%252592%2525E8%252581%252594%2525E7%2525BD%252591%2525E8%252581%25258C%2525E4%2525B8%25259A%2525E6%25259C%2525BA%2526xp%253Did%28%252522m6c247d9c%252522%29%25252FDIV%25255B1%25255D%25252FDIV%25255B1%25255D%25252FDIV%25255B1%25255D%25252FDIV%25255B1%25255D%25252FH2%25255B1%25255D%25252FA%25255B1%25255D%2526linkType%253D%2526checksum%253D220%26ie%3Dutf-8%26f%3D8%26tn%3Dbaidu%26wd%3D%25E6%258B%2589%25E5%258B%25BE%25E7%25BD%2591%26oq%3D%2525E6%25259D%2525AD%2525E5%2525B7%25259E%2525E7%252594%2525B5%2525E5%2525AD%252590%2525E7%2525A7%252591%2525E6%25258A%252580%2525E5%2525A4%2525A7%2525E5%2525AD%2525A6%26rqlang%3Dcn%26inputT%3D2518; PRE_LAND=https%3A%2F%2Fwww.lagou.com%2F%3Futm_source%3Dm_cf_cpt_baidu_pc; LGUID=20171215142351-84d785f4-e160-11e7-9a0b-525400f775ce; X_HTTP_TOKEN=352f0849051a7bc84ed05f3ba6808fe9; _putrc=7E09D7EE60C821B7; login=true; unick=%E5%90%B4%E4%BF%8A%E4%BA%9A; showExpriedIndex=1; showExpriedCompanyHome=1; showExpriedMyPublish=1; hasDeliver=0; index_location_city=%E5%8C%97%E4%BA%AC; Hm_lpvt_4233e74dff0ae5bd0a3d81c6ccf756e6=1513319596; LGRID=20171215143204-aa3d51ef-e161-11e7-9a28-525400f775ce; TG-TRACK-CODE=index_search",
            "Host": "www.lagou.com",
            'Origin': 'https://www.lagou.com',
            'Referer': 'https://www.lagou.com/jobs/list_%E6%95%B0%E6%8D%AE%E5%88%86%E6%9E%90?city=%E5%8C%97%E4%BA%AC&cl=false&fromSearch=true&labelWords=&suginput=',
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/63.0.3239.84 Safari/537.36'}

        self.post_data = {'first': 'false', 'pn':'1', 'kd':'爬虫工程师' }#这是请求网址的一些参数

        with open("8.csv","a",encoding="GBK") as f:
            f.write("公司,工作,年限,学历,薪资,城市,福利,规模,要求,网址"+ "\n")
        self.r = redis.Redis("127.0.0.1", 6379)
        self.item_key = "lg"



    def parse_url_get(self,url):
        print(self.headers)
        try:
            response = requests.get(url,headers=self.headers).text
        except:
            return None

        return response


    def parse_url_post(self,url,data):

        response = requests.post(url,headers=self.headers,data=data).text
        return response


    def get_content_list(self,json_res):
        dict_res = json.loads(json_res)
        result_list = dict_res["content"]["positionResult"]["result"]
        # print(result_list)
        # 列表页：公司名称、职位、年限、经验、薪资、地址
        # 详情页：福利、职责、职位要求、公司规模、网址
        list_con = []
        for result in result_list:
            dict = {}
            dict["ltd"] = result["companyShortName"]
            dict["job"] = result["positionName"]
            dict["year"] = result["workYear"]
            dict["edu"] = result["education"]
            dict["money"] = result["salary"]
            dict["city"] = result["city"]
            detail_url = ("https://www.lagou.com/jobs/"+str(result["positionId"])+".html" ) if len(str(result["positionId"]))>0 else None
            if detail_url is not None:
                dict = self.get_detail_data(detail_url,dict)

            list_con.append(dict)

        return list_con


    def get_detail_data(self,detail_url,dict):

        str_html = self.parse_url_get(detail_url)
        html = etree.HTML(str_html)
        dict["people"] = html.xpath("//ul[@class='c_feature']/li[last()-1]/text()")[1].strip()
        print(dict["people"])
        dict["ltd_href"] = html.xpath("//ul[@class='c_feature'][last()]//a/@href")[0]

        dict["fuli"] = html.xpath("//dd[@class='job-advantage']/p/text()")[0]


        text_list = html.xpath("//h3[@class='description']/following-sibling::div[1]/p/text()")
        text = ""
        for item in text_list:
            text = text + item +"\n"
        dict["yaoqiu"]= text

        print(dict)
        return dict


    # def save_content_list(self,list_con):
    #     for each in list_con:
    #         with open("6.csv","a",encoding="GBK") as f:
    #             temp_list = [each["ltd"], each["job"], each["year"], each["edu"], each["money"], each["city"]]
    #             # print(temp_list) 保存csv的临时列表
    #             temp_str = ",".join([str(i) for i in temp_list])+"\n"
    #             f.write(temp_str)

    def item_dupfilter(self,dict):
        f = hashlib.sha1()
        f.update(dict["ltd"].encode())
        f.update(dict["job"].encode())

        # f.update(dict["author"].encode())
        fingerprint = f.hexdigest()
        print(fingerprint)
        res = self.r.sadd (self.item_key,fingerprint)
        return res

    def save_mysql(self,con_list):
        conn = connect(host="localhost",
                       user="root",
                       password="mysql",
                       database="lagou",
                       port=3306,
                       charset='utf8')
        for i,dict in enumerate(con_list):

            cur = conn.cursor()  # 数据库链接对象
            res = self.item_dupfilter(dict)
            if res==1:
                if "爬虫" in dict["job"]:
                    print("存入i爬虫")
                    sql = "insert IGNORE into pc SET"
                elif "人工智能" in dict["job"]:
                    print("存入i人工智能")
                    sql = "insert IGNORE into rg SET"
                else:
                    print('存入i分析')
                    sql = "insert IGNORE into fx SET"

                for key, value in dict.items():
                    res = "`{}` = '{}'".format(key, value)
                    sql = sql + ' ' + res + ','
                sql = sql[:-1]
                sql = sql + ';'

            else:
                if "爬虫" in dict["job"]:
                    print('更新爬虫')
                    sql = "update pc SET"
                elif "人工智能" in dict["job"]:
                    print("更新i人工智能")
                    sql = "update rg SET"
                else:
                    print('更新分析')
                    sql = "update fx SET"

                for key, value in dict.items():
                    res = "`{}` = '{}'".format(key, value)
                    sql = sql + ' ' + res + ','
                sql = sql[:-1]
                sql = sql + " where job='{}' and ltd='{}'".format(dict["job"],dict["ltd"])
                sql = sql + ';'
            print(i,sql)
            try:
                cur.execute(sql)
            except Exception as ret:
                print(ret)
            conn.commit()
            cur.close()
        conn.close()

    def save_content_list(self,list_con):
        with open('8.csv', 'a',encoding="utf8") as f:
            writer = csv.writer(f)
            # writer.writerow(['company_name', 'emails', 'website', 'url'])
            for t in list_con:
                ltd = t["ltd"]
                job = t["job"]
                year = t["year"]
                edu = t["edu"]
                money = t["money"]
                city = t["city"]
                fuli=t["fuli"]
                yaoqiu=t["yaoqiu"]
                people = t["people"]
                ltd_href = t["ltd_href"]

                data = [(ltd, job, year, edu,money,city,fuli,yaoqiu,people,ltd_href)]
                writer.writerows(data)
        f.close()



    def run(self):
        cityList = ['上海',"北京"]
        jobList=["爬虫工程师","数据分析师","人工智能工程师"]
        for city in cityList:
            print('爬取%s' % city)
            myurl = 'https://www.lagou.com/jobs/positionAjax.json?city={}&needAddtionalResult=false&isSchoolJob=0'.format(city)
            for i in range(1,5):
                self.post_data["pn"] = i
                for job in jobList:
                    self.post_data["kd"]=job
                    print(self.post_data)
                    json_res = self.parse_url_post(myurl,self.post_data)
                    # print(json_response)
                    list_con= self.get_content_list(json_res)
                    self.save_content_list(list_con)
                    self.save_mysql(list_con)
                    time.sleep(2)



if __name__ == '__main__':
    lgpost = LgPost()
    lgpost.run()



