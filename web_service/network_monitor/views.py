from datetime import datetime
import calendar
import time

from django.shortcuts import render
from django.http import HttpResponse, HttpResponseRedirect

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



def history_graph_user_host_time(request, user_mac):
    
    start = request.POST.get('date_start')
    end   = request.POST.get('date_end')
    if start and end:
        start = int(datetime.strptime(start, '%Y-%m-%dT%H:%M').strftime("%s"))
        end = int(datetime.strptime(end, '%Y-%m-%dT%I:%M').strftime("%s"))
        history_list = History.objects.filter(client__exact=user_mac).filter(date__gte=start).filter(date__lte=end).order_by('host', 'date')
    else:
        history_list = History.objects.filter(client__exact=user_mac).order_by('host', 'date')
    
    if (not history_list):
        return HttpResponseRedirect(reverse('history_graph_users_time'))

    user_graph_list = []
    other_hosts = {'value': [], 'hosts' : ''}
    cur_host = None
    for idx, element in enumerate(history_list):
        if element.host != cur_host:
            #if idx + 1 < len(history_list) and element.host == history_list[idx+1].host:# and element.host == history_list[idx+2].host:
            cur_host = element.host
            user_graph_list.append({'host': element.host, 'value': [{'first': element.date, 'second': element.value}]})
            '''else:
                other_value = next((x for x in other_hosts['value'] if x['first'] == element.date), None)
                if other_value:
                    print(element.host)
                    other_value['second'] += element.value
                else:
                    other_hosts['value'].append({'first': element.date, 'second': element.value})
                other_hosts['hosts'] += element.host + ' ' 
            '''
        else:
            user_graph_list[-1]['value'].append({'first': element.date, 'second': element.value})
    
    [user_graph_list, other_hosts_aux] = getCommonHosts(user_graph_list, 8)
    #other_hosts['hosts'] = other_hosts_aux['hosts'] + ' ' + other_hosts['hosts']
    
    if (other_hosts_aux != None):
        other_hosts['value'].extend(other_hosts_aux['value'])
    other_hosts['value'] = sorted(other_hosts['value'], key=lambda value: value['first']) 
    
    print(user_graph_list)
    print(other_hosts)    
    
    context = {'user_graph_list': user_graph_list , 'other_hosts': other_hosts, "client": user_mac }
    return render(request, 'network_monitor/history_graph_user.html', context)



def history_graph_users_time(request):
    start = request.POST.get('date_start')
    end   = request.POST.get('date_end')
    if start and end:
        start = int(datetime.strptime(start, '%Y-%m-%dT%H:%M').strftime("%s"))
        end = int(datetime.strptime(end, '%Y-%m-%dT%I:%M').strftime("%s"))
        history_list = History.objects.order_by('date').filter(date__gte=start).filter(date__lte=end)
    else:
        history_list = History.objects.order_by('client','date')

    users_time_list = []
    clients_list = []
    cur_client = None
    for element in history_list:
        if element.client != cur_client:
            cur_client = element.client
            clients_list.append(element.client)
            users_time_list.append({'client': element.client, 'value': [{'first': element.date, 'second': element.value}]})
        elif element.date == users_time_list[-1]['value'][-1]['first']:
            users_time_list[-1]['value'][-1]['second'] += element.value 
        else:
            users_time_list[-1]['value'].append({'first': element.date, 'second': element.value})
    
    context = {'users_time_list': users_time_list, 'clients_list': clients_list}
    return render(request, 'network_monitor/history_graph_users_time.html', context)



def getCommonHosts(user_graph_list, best_no):
    note = []
    for element in user_graph_list:
        sum = 0
        for axis in element['value']:
            sum += axis['second'] 
        note.append({'host': element['host'], 'total_value': (len(element['value'] * sum))})
    
    note = sorted(note, key=lambda elem: elem['total_value'], reverse=True)
    #new_list = sorted(user_graph_list, key=lambda elem: for n in note: if n['host'] == elem[host]: n['total_value'])
    new_list = []
    for n in note:
        for elem in user_graph_list:
            if n['host'] == elem['host']:
                new_list.append(elem)
    
    if best_no >= len(user_graph_list):
        return [new_list, None]
    else:
        other_hosts_aux = {'value': [], 'hosts' : ''}
        for elem in new_list[best_no:]:
            other_hosts_aux['hosts'] += elem['host'] + ' '
            other_hosts_aux['value'].extend(elem['value'])
        return [new_list[:best_no], other_hosts_aux]




