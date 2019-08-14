
import tornado.ioloop
import tornado.web

class BaseHandler(tornado.web.RequestHandler):
    def get_current_user(self):
        return self.get_secure_cookie("user")

class MainHandler(BaseHandler):
    @tornado.web.authenticated
    def get(self):
        name = tornado.escape.xhtml_escape(self.current_user)
        self.write("Hello " + name)

settings = {
        "cookie_secret": "61oETzKXQAGaYdkL5gEmGeJJFuYh7EQnp2XdTP1o/Vo=",
        "login_url": "/login",
        "xsrf_cookies": True,
        }

class LoginHandler(BaseHandler):
    def get(self):
        self.write(
                '<html><body>'
                    '<form action="/login" method="post">'
                        'Name: <input type="text" name="name" />'
                        '<input type="submit" value="Sign in" />'
                    '</form>'
                '</body></html>'
                )
        self.render("2-template.html")

    def post(self):
        self.set_secure_cookie("user", self.get_argument("name"))
        self.redirect("/")

class NewMsgHandler(BaseHandler):

    def post(self):
        self.set_secure_cookie("user", self.get_argument("message"))
        self.redirect("/")

def make_app():
    return tornado.web.Application([
        (r"/", MainHandler),
        (r"/login", LoginHandler),
        (r"/new_message", NewMsgHandler),
        ], **settings)

if __name__ == "__main__":
    app = make_app()
    app.listen(8080)
    tornado.ioloop.IOLoop.instance().start()
