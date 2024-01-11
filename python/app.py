from flask import Flask
from db import db, User
from elo import update_elo_rating
from auth import authorize_user, get_access_token
from flask_jwt_extended import JWTManager

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///site.db'
app.config['JWT_SECRET_KEY'] = 'apl_2023-2024_project'
db.init_app(app)
jwt = JWTManager(app)

# Combine route decorators for better readability
@app.route('/api/update_elo', methods=['POST'])
def update_elo():
    return update_elo_rating()

@app.route('/api/authorize', methods=['POST'])
def authorize():
    return authorize_user()

@app.route('/api/get_token', methods=['GET'])
def get_token():
    return get_access_token()

if __name__ == "__main__":
    app.run(host='0.0.0.0', port=5000)