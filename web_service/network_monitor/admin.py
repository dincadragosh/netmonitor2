from django.contrib import admin
from network_monitor.models import History, HTTPReqInfo

class HistoryAdmin(admin.ModelAdmin):
    list_display = ('getDate', 'client', 'host')

admin.site.register(History, HistoryAdmin)
admin.site.register(HTTPReqInfo)
