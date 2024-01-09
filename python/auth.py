from flask import request, jsonify
from werkzeug.security import generate_password_hash, check_password_hash
from flask_jwt_extended import create_access_token
from db import db, User, Token

def authorize_user():
    data = request.get_json()
    username = data.get("username")
    password = data.get("password")
    user = User.query.filter_by(username=username).first()

    if user is None:
        hashed_password = generate_password_hash(password)
        new_user = User(username=username, password=hashed_password)
        db.session.add(new_user)
        db.session.commit()

    if check_password_hash(user.password, password):
        access_token = create_access_token(identity=username)
        save_access_token_on_server(username, access_token)
        return jsonify({"message": "Authorization successful", "access_token": access_token}), 200
    else:
        return jsonify({"error": "Invalid credentials"}), 401

def save_access_token_on_server(username, access_token):
    existing_token = Token.query.filter_by(username=username).first()

    if existing_token:
        existing_token.access_token = access_token
    else:
        new_token = Token(username=username, access_token=access_token)
        db.session.add(new_token)

    db.session.commit()

def get_access_token():
    username = request.args.get('username')

    if not username:
        return jsonify({"error": "Username parameter is missing"}), 400

    user = User.query.filter_by(username=username).first()

    if not user:
        return jsonify({"error": "User not found"}), 404

    token = Token.query.filter_by(username=username).first()

    if not token:
        return jsonify({"error": "Token not found for the user"}), 404

    return jsonify({"username": username, "access_token": token.access_token}), 200