from flask import jsonify, request
from db import db, User
import math

def calc_new_elo_rating(player_rating, opponent_rating, player_won):
    k_factor = 24
    expected_score = 1 / (1 + math.pow(10, (opponent_rating - player_rating) / 400))
    new_rating = player_rating + k_factor * (player_won - expected_score)
    return int(new_rating)

def update_elo_rating():
    p1_won = (request.args.get("p1_won", "").lower() == "true")
    p1_username = request.args.get("p1_username")
    p2_username = request.args.get("p2_username")

    p1_user = User.query.filter_by(username=p1_username).first()
    p2_user = User.query.filter_by(username=p2_username).first()

    if p1_user is None or p2_user is None:
        return jsonify({"error": "User not found"}), 404

    p1_current_rating = p1_user.rating
    p2_current_rating = p2_user.rating
    
    p1_new_rating = calc_new_elo_rating(p1_current_rating, p2_current_rating, p1_won)
    p2_new_rating = calc_new_elo_rating(p2_current_rating, p1_current_rating, not p1_won)

    p1_user.rating = p1_new_rating
    p2_user.rating = p2_new_rating

    db.session.commit()

    return jsonify({"player1_new_rating": p1_new_rating, "player2_new_rating": p2_new_rating})

def get_elo_rating():
    player_username = request.args.get("player_username")
    player = User.query.filter_by(username=player_username).first()
    if player is None:
        return jsonify({"error": "User not found"}), 404
    
    player_rating = player.rating
    return jsonify({"player_rating": player_rating})