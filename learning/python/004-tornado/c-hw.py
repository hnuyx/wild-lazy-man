
import tornado.ioloop
import tornado.web

class MainHandler(tornado.web.RequestHandler):
    def get(self):
        self.write(''
            '<html><body><form action="/" method="post">'
                '<input type="text" name="message">'
                '<input type="submit" value="Submit">'
            '</form></body></html>')
    def post(self):
        self.set_header("Content-type", "text/plain")
        self.write("You worte " + self.get_argument("message"))

class StoryHandler(tornado.web.RequestHandler):
    def get(self, story_id):
        self.write("You requested the story " + story_id)

def make_app():
    return tornado.web.Application([
        (r"/", MainHandler),
        (r"/story/([0-9]+)", StoryHandler),
        ])

if __name__ == "__main__":
    app = make_app()
    app.listen(8080)
    tornado.ioloop.IOLoop.instance().start()
