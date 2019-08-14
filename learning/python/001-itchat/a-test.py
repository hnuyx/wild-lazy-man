
import itchat

@itchat.msg_register(itchat.content.TEXT)
def echo(msg):
    return msg.text

if __name__ == '__main__':
    itchat.auto_login()
    itchat.run()
