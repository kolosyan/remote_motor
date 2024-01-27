# users/forms.py
from django.contrib.auth import get_user_model
from django.contrib.auth.forms import UserCreationForm
from .models import Users

user = get_user_model
class UserCreationForm(UserCreationForm):
    class Meta(UserCreationForm.Meta):

        model = Users
        fields = UserCreationForm.Meta.fields  # Include other fields if needed
