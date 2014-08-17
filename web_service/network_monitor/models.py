from django.db import models
import time

class History(models.Model):
    date   = models.BigIntegerField()
    client = models.CharField(max_length=20)
    host   = models.CharField(max_length=50)
    value  = models.IntegerField(default=0)
    
    def __unicode__(self):  # Python 3: def __str__(self):
        return self.getDate() + " " + self.client + " " + self.host 

    def getDate(self):
        return time.strftime("%Y-%m-%d %H:%M:%S", time.gmtime(self.date)) 

class HTTPReqInfo(models.Model):
    history = models.ForeignKey(History)
    request = models.CharField(max_length=100)

