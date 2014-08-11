from django.db import models

class History(models.Model):
    date   = models.DateTimeField()
    client = models.CharField(max_length=20)
    host   = models.CharField(max_length=50)
    value  = models.IntegerField(default=0)

class HTTPReqInfo(models.Model):
    history = models.ForeignKey(History)
    request = models.CharField(max_length=100)

