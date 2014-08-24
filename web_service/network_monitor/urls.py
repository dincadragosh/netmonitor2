from django.conf.urls import patterns, url
from network_monitor import views

urlpatterns = patterns('',
    url(r'^$', views.history_graph_users_time, name='history_graph_users_time'),
    url(r'^history_table$', views.history_table, name='history_table'),
    url(r'^history_graph_user1/(?P<user_mac>.+)/$', views.history_graph_user_host_time, name='history_graph_user_host_time'),
)
