from flask import jsonify, request
from db import db, User
import math

def calc_new_elo_rating(player_rating, opponent_rating, result):
    k_factor = 24
    expected_score = 1 / (1 + math.pow(10, (opponent_rating - player_rating) / 400))
    new_rating = player_rating + k_factor * (result - expected_score)
    return int(new_rating)

def update_elo_rating():
    data = request.get_json()
    result = data.get("result")
    p1_username = data.get("player1_username")  # Adjust to use 'username' instead of 'id'
    p2_username = data.get("player2_username")

    p1_user = User.query.filter_by(username=p1_username).first()
    p2_user = User.query.filter_by(username=p2_username).first()

    if p1_user is None or p2_user is None:
        return jsonify({"error": "User not found"}), 404

    p1_current_rating = p1_user.rating
    p2_current_rating = p2_user.rating
    
    p1_new_rating = calc_new_elo_rating(p1_current_rating, p2_current_rating, result)
    p2_new_rating = calc_new_elo_rating(p2_current_rating, p1_current_rating, 1 - result)

    p1_user.rating = p1_new_rating
    p2_user.rating = p2_new_rating

    db.session.commit()

    return jsonify({"player1_new_rating": p1_new_rating, "player2_new_rating": p2_new_rating})