from flask_sqlalchemy import SQLAlchemy
from datetime import datetime, timedelta

db = SQLAlchemy()

class User(db.Model):
    username = db.Column(db.String(20), primary_key=True, unique=True, nullable=False)
    password = db.Column(db.String(128), nullable=False)  # Storing hashed passwords
    rating = db.Column(db.Integer, default=1200)
    created_at = db.Column(db.DateTime, default=datetime.utcnow)
    token = db.relationship('Token', backref='user', uselist=False)

    def __repr__(self):
        return f"User('{self.username}', '{self.rating}')"

class Token(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(20), db.ForeignKey('user.username'), unique=True, nullable=False)
    access_token = db.Column(db.String(500), nullable=False)
    expiration_time = db.Column(db.DateTime, default=datetime.utcnow() + timedelta(minutes=30))

    def __repr__(self):
        return f"Token('{self.username}', '{self.access_token}')"