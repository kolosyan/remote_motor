from .routing import ProtocolTypeRouter, URLRouter
from django.urls import path
from . import consumers

application = ProtocolTypeRouter(
    {
        "websocket": URLRouter(
            [
                path("ws/mqtt/", consumers.MQTTConsumer.as_asgi()),
            ]
        ),
    }
)
