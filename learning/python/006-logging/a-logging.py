
import logging
from logging.handlers import TimedRotatingFileHandler

from time import sleep

logHandler = TimedRotatingFileHandler("logfile", when="midnight")
logFormatter = logging.Formatter("%(asctime)s %(name)-12s %(levelname)-8s %(message)s")
logHandler.setFormatter(logFormatter)
logger = logging.getLogger("MyLogger")
logger.addHandler(logHandler)
logger.setLevel(logging.INFO)

i = 0;
while True:
    i = i + 1
    logger.info("Line %d" % i)
    sleep(5)
