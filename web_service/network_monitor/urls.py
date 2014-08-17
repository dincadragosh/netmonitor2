from django.conf.urls import patterns, url
from network_monitor import views

urlpatterns = patterns('',
    url(r'^$', views.history_table, name='history_table'),
    url(r'^history_graph_user', views.history_graph_user, name='history_graph_user')
)
