# web api
# http://docs.cherrypy.org/en/latest/tutorials.html#tutorial-5-track-my-end-user-s-activity

import random
import string

import cherrypy

class StringGenerateOrWebservice(object):
	exposed = True

	@cherrypy.tools.accept(media='text/plain')
	def GET(self):
		return cherrypy.session['rd_string']

	def POST(self, length=8):
		some_string = ''.join(random.sample(string.hexdigits, int(length)))
		cherrypy.session['rd_string'] = some_string
		return some_string

	def PUT(self, another_string):
		cherrypy.session['rd_string'] = another_string

	def DELETE(self):
		cherrypy.session.pop('rd_string', None)

if __name__ == '__main__':
	conf = {
		'/': {
			'request.dispatch': cherrypy.dispatch.MethodDispatcher(),
			'tools.sessions.on': True,
			'tools.response_headers.on': True,
			'tools.response_headers.headers': [('Content-Type', 'text/plain')]
		}
	}
	cherrypy.quickstart(StringGenerateOrWebservice(), '/', conf)
