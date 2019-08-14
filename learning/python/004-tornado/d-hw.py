
import tornado.ioloop
import tornado.web

class MainHandler(tornado.web.RequestHandler):
    def get(self):
        items = ["items1", "items2", "itmes3"]
        self.render("1-template.html", title="My title", items=items)

def make_app():
    return tornado.web.Application([
        (r"/", MainHandler),
        ])

if __name__ == "__main__":
    app = make_app()
    app.listen(8080)
    tornado.ioloop.IOLoop.instance().start()
