from django.contrib import admin
from network_monitor.models import History, HTTPReqInfo

admin.site.register(History)
admin.site.register(HTTPReqInfo)
