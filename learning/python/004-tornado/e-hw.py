
import tornado.ioloop
import tornado.web

class BaseHandler(tornado.web.RequestHandler):
    def get_current_user(self):
        return self.get_secure_cookie("user")

class MainHandler(BaseHandler):
    def get(self):
        if not self.current_user:
            self.redirect("/login")
            return
        name = tornado.escape.xhtml_escape(self.current_user)
        self.write("Hello " + name)

class LoginHandler(BaseHandler):
    def get(self):
        self.write(
                '<html><body>'
                    '<form action="/login" method="post">'
                        'Name: <input type="text" name="name">'
                        '<input type="submit" value="Sign in">'
                    '</form>'
                '</body></html>'
                )
    def post(self):
        self.set_secure_cookie("user", self.get_argument("name"))
        self.redirect("/")

def make_app():
    return tornado.web.Application([
        (r"/", MainHandler),
        (r"/login", LoginHandler),
        ], cookie_secret="61oETzKXQAGaYdkL5gEmGeJJFuYh7EQnp2XdTP1o/Vo=")

if __name__ == "__main__":
    app = make_app()
    app.listen(8080)
    tornado.ioloop.IOLoop.instance().start()
