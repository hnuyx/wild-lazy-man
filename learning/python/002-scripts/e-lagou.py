# -*- coding: UTF-8 -*-
import json
import requests
import time
#headers内容,网页上会有，其中cooies就包括登录的效果，暂时简单理解为：拉勾网不会因为我们的操作频繁而阻止

class LgPost(object):
    def __init__(self):
        self.headers = {
            "Cookie":"JSESSIONID=ABAAABAAADEAAFIF0390879C909ED6B25B79466EE283BE3; _ga=GA1.2.417433648.1513319104; _gid=GA1.2.1618013105.1513319104; Hm_lvt_4233e74dff0ae5bd0a3d81c6ccf756e6=1513319105; user_trace_token=20171215142351-84d77e04-e160-11e7-9a0b-525400f775ce; LGSID=20171215142351-84d782ed-e160-11e7-9a0b-525400f775ce; PRE_UTM=m_cf_cpt_baidu_pc; PRE_HOST=bzclk.baidu.com; PRE_SITE=http%3A%2F%2Fbzclk.baidu.com%2Fadrc.php%3Ft%3D06KL00c00f7Ghk60yUKm0FNkUs0dpWPp00000PW4pNb00000zJBmtg.THL0oUhY1x60UWdBmy-bIfK15yRvujDYnvf3nj0snADdrAm0IHYznDNAf1mdPbD3wjDvPjmkn1c3PHfsPYf3nRfsP16zw0K95gTqFhdWpyfqn101n1csPHnsPausThqbpyfqnHm0uHdCIZwsT1CEQLILIz4_myIEIi4WUvYE5LNYUNq1ULNzmvRqUNqWu-qWTZwxmh7GuZNxTAn0mLFW5HRLrjDL%26tpl%3Dtpl_10085_15730_11224%26l%3D1500117464%26attach%3Dlocation%253D%2526linkName%253D%2525E6%2525A0%252587%2525E9%2525A2%252598%2526linkText%253D%2525E3%252580%252590%2525E6%25258B%252589%2525E5%25258B%2525BE%2525E7%2525BD%252591%2525E3%252580%252591%2525E5%2525AE%252598%2525E7%2525BD%252591-%2525E4%2525B8%252593%2525E6%2525B3%2525A8%2525E4%2525BA%252592%2525E8%252581%252594%2525E7%2525BD%252591%2525E8%252581%25258C%2525E4%2525B8%25259A%2525E6%25259C%2525BA%2526xp%253Did%28%252522m6c247d9c%252522%29%25252FDIV%25255B1%25255D%25252FDIV%25255B1%25255D%25252FDIV%25255B1%25255D%25252FDIV%25255B1%25255D%25252FH2%25255B1%25255D%25252FA%25255B1%25255D%2526linkType%253D%2526checksum%253D220%26ie%3Dutf-8%26f%3D8%26tn%3Dbaidu%26wd%3D%25E6%258B%2589%25E5%258B%25BE%25E7%25BD%2591%26oq%3D%2525E6%25259D%2525AD%2525E5%2525B7%25259E%2525E7%252594%2525B5%2525E5%2525AD%252590%2525E7%2525A7%252591%2525E6%25258A%252580%2525E5%2525A4%2525A7%2525E5%2525AD%2525A6%26rqlang%3Dcn%26inputT%3D2518; PRE_LAND=https%3A%2F%2Fwww.lagou.com%2F%3Futm_source%3Dm_cf_cpt_baidu_pc; LGUID=20171215142351-84d785f4-e160-11e7-9a0b-525400f775ce; X_HTTP_TOKEN=352f0849051a7bc84ed05f3ba6808fe9; _putrc=7E09D7EE60C821B7; login=true; unick=%E5%90%B4%E4%BF%8A%E4%BA%9A; showExpriedIndex=1; showExpriedCompanyHome=1; showExpriedMyPublish=1; hasDeliver=0; index_location_city=%E5%8C%97%E4%BA%AC; Hm_lpvt_4233e74dff0ae5bd0a3d81c6ccf756e6=1513319596; LGRID=20171215143204-aa3d51ef-e161-11e7-9a28-525400f775ce; TG-TRACK-CODE=index_search",
            "Host": "www.lagou.com",
            'Origin': 'https://www.lagou.com',
            'Referer': 'https://www.lagou.com/jobs/list_%E6%95%B0%E6%8D%AE%E5%88%86%E6%9E%90?city=%E5%8C%97%E4%BA%AC&cl=false&fromSearch=true&labelWords=&suginput=',
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/63.0.3239.84 Safari/537.36'}

        with open("6.csv","a",encoding="GBK") as f:
            f.write("公司,工作,年限,学历,薪资,城市"+ "\n")

    def parse_url(self,url):
        post_data = {'first': 'false', 'pn': '1', 'kd': '爬虫工程师'}  # 这是请求网址的一些参数
        response = requests.post(url,headers=self.headers,data=post_data).text
        return response,post_data


    def get_content_list(self,json_res):
        dict_res = json.loads(json_res)
        result_list = dict_res["content"]["positionResult"]["result"]
        # print(result_list)
        list_con = []
        for result in result_list:
            dict = {}
            dict["ltd"] = result["companyShortName"]
            dict["job"] = result["positionName"]
            dict["year"] = result["workYear"]
            dict["edu"] = result["education"]
            dict["money"] = result["salary"]
            dict["city"] = result["city"]
            print(dict)
            list_con.append(dict)

        return list_con


    def save_content_list(self,list_con):
        for each in list_con:
            with open("6.csv","a",encoding="GBK") as f:
                temp_list = [each["ltd"], each["job"], each["year"], each["edu"], each["money"], each["city"]]
                # print(temp_list) 保存csv的临时列表
                temp_str = ",".join([str(i) for i in temp_list])+"\n"
                f.write(temp_str)


    def run(self):
        cityList = ['上海']
        for city in cityList:
            print('爬取%s' % city)
            myurl = 'https://www.lagou.com/jobs/positionAjax.json?city={}&needAddtionalResult=false&isSchoolJob=0'.format(city)
            for i in range(1,10):
                # print(self.headers["Host"])
                # print(self.post_data["pn"])

                json_res,post_data = self.parse_url(myurl)
                post_data["pn"] = i  # 错误方法，这样会一直打印第一页的数据
                print(post_data)
                # print(json_response)
                list_con = self.get_content_list(json_res)
                self.save_content_list(list_con)
                time.sleep(3)






if __name__ == '__main__':
    lgpost = LgPost()
    lgpost.run()



