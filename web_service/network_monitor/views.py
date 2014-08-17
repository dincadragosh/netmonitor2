from datetime import datetime
import calendar
import time

from django.shortcuts import render
from django.http import HttpResponse

from network_monitor.models import History


def history_table(request):
    start = request.POST.get('date_start')
    end   = request.POST.get('date_end')
    if start and end:
        start = int(datetime.strptime(start, '%Y-%m-%dT%H:%M').strftime("%s")) 
        end = int(datetime.strptime(end, '%Y-%m-%dT%I:%M').strftime("%s"))
        history_list = History.objects.order_by('date').filter(date__gte=start).filter(date__lte=end)
    else:
        history_list = History.objects.order_by('host','date')
    context = {'history_list': history_list}
    return render(request, 'network_monitor/history_table.html', context)

def history_graph_user(request):
    start = request.POST.get('date_start')
    end   = request.POST.get('date_end')
    if start and end:
        start = int(datetime.strptime(start, '%Y-%m-%dT%H:%M').strftime("%s"))
        end = int(datetime.strptime(end, '%Y-%m-%dT%I:%M').strftime("%s"))
        history_list = History.objects.order_by('date').filter(date__gte=start).filter(date__lte=end)
    else:
        history_list = History.objects.order_by('host','date')
    
    user_graph_list = []
    cur_host = None
    for element in history_list:
        if element.host != cur_host:
            cur_host = element.host
            user_graph_list.append({'host': element.host, 'value': [{'first': element.date, 'second': element.value}]})
        else:
            user_graph_list[-1]['value'].append({'first': element.date, 'second': element.value})
    print(user_graph_list)    

    context = {'user_graph_list': user_graph_list}
    return render(request, 'network_monitor/history_graph_user.html', context)
