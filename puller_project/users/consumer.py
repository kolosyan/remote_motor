import json
import paho.mqtt.publish as publish
import channels
from channels.generic.websocket import AsyncWebsocketConsumer



class MQTTConsumer(AsyncWebsocketConsumer):
    async def connect(self):
        await self.accept()

    async def disconnect(self, close_code):
        pass

    async def receive(self, text_data):
        payload = json.loads(text_data)
        topic = payload['topic']
        message = payload['message']
        publish.single(topic, message, hostname="localhost")

        await self.send(text_data=json.dumps({'message': f"Sent to {topic}: {message}"}))
