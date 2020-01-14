from requests_html import HTMLSession
from time import sleep
from fake_useragent import UserAgent
import json
import urllib.parse
import csv
import work
import city
 
kds = work.works
cities = city.cities
ua = UserAgent()
url = 'https://www.lagou.com/jobs/positionAjax.json'
csvfile = open('data.csv', 'a+',encoding = 'utf-8')
writer = csv.writer(csvfile)
needHeader = False

for kd in kds:
    session = HTMLSession()
    enkd = urllib.parse.quote(kd)

    def getCookies():
        global session
        session = HTMLSession()
        session.get(
            url=f'https://www.lagou.com/jobs/list_{kd}?fromSearch=true',
            headers={
                'useragent': UserAgent().random})
        # sleep(0.5)
    getCookies()
    for city in cities:
        encity = urllib.parse.quote(city)
        headers = {
            'user-agent': ua.random,
            'referer': f'https://www.lagou.com/jobs/list_{enkd}?city={encity}&cl=false&fromSearch=true',
            'Origin': 'https://www.lagou.com',
            'Accept': 'application/json, text/javascript, */*; q=0.01',
            'Content-Type': 'application/x-www-form-urlencoded; charset=UTF-8'
        }

        data = {
            'first': 'true',
            'pn': 1,
            'kd': kd,
            'city': city,
            'needAddtionalResult': 'false'
        }

        while (True):
            data['first'] = 'false' if data['pn'] > 1 else 'true'
            r = session.post(
                url=url,
                headers=headers,
                data=data
            )
            content = r.content
            json_msg = json.loads(content)
            if not json_msg.__contains__('content'):
                getCookies()
                continue
            lists = json_msg['content']['positionResult']['result']
            if len(lists) == 0 or lists[0]['city'] != city:
                break
            for info in lists:
                del info['companyLogo']
                del info['explain']
                del info['plus']
                del info['promotionScoreExplain']
                del info['gradeDescription']
                del info['hitags']
                del info['positionLables']
                del info['pcShow']
                del info['appShow']
                if needHeader:
                    writer.writerow(list(info.keys()))
                    needHeader = False
                writer.writerow(list(info.values()))
            print(f"{city} {kd} {data['pn']}")
            data['pn'] += 1
            if len(lists) < 15:
                break

csvfile.close()