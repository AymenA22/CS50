import os
import datetime

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///notes.db")

@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    user_id = session["user_id"]
    transactions_db = db.execute("SELECT symbol, SUM(shares) AS shares, price FROM transactions WHERE user_id = ? GROUP BY symbol", user_id)
    cash_db = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
    cash = "{:.2f}".format(cash_db[0]["cash"])
    total_shares_value = sum(transaction["shares"] * transaction["price"] for transaction in transactions_db)
    total_shares_value = "{:.2f}".format(total_shares_value)
    return render_template("index.html",
                           transactions_database = transactions_db,
                           cash = cash,
                           total = total_shares_value,
                           )


@app.route("/Add", methods=["GET", "POST"])
@login_required
def add():
    """Add Note, Reminder or To-Do Event"""

    # If method is GET return to add.html else POST
    if request.method == "GET":
        return render_template("add.html")

    else:
        event = request.form.get("event")
        shares = int(request.form.get("shares"))

        if not symbol:
            return apology("please input a symbol")

        event = lookup(symbol.upper())

        if stock == None:
            return apology("This symbol does not exist")

        # if the share is less than zero return apology for share not allowed
        if shares < 1:
            return apology("You must purchase at least one share")

        # Does the user have enough money?
        transaction_value = shares * float(stock["price"])

        user_id = session["user_id"]

        user_cash_db = db.execute("SELECT cash FROM users WHERE id = ?", user_id)

        # Get the first instance of cash from the database for the user
        user_cash = user_cash_db[0]["cash"]

        # If the cash is more than the transaction value then can continue
        if user_cash < transaction_value:
            return apology("Not enought money for this transaction.")

        # Update the user table

        update_cash = user_cash - transaction_value

        # Update the database
        db.execute("UPDATE users SET cash = ? WHERE id = ?", update_cash, user_id)

        # Add a new row to the transaction database with a timestamp
        transaction_date = datetime.datetime.now()

        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, date) VALUES (?, ?, ?, ?, ?)", user_id, stock["symbol"], shares, stock["price"], transaction_date)

        # Display a message using flash
        flash("Shares purchased")

        return redirect("/")


@app.route("/Notes")
@login_required
def notes():
    """Show history of transactions"""
    user_id = session["user_id"]

    #transactions_db = db.execute("SELECT id, symbol, shares, price, date FROM transactions WHERE user_id = ?", user_id)
    transactions_db = db.execute("SELECT * FROM transactions WHERE user_id = ?", user_id)

    #cash_db = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
    #cash = "{:.2f}".format(cash_db[0]["cash"])
    #return render_template("history.html", database = transactions_db, cash = cash)

    return render_template("Notes.html", transactions_database = transactions_db)



@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/Reminders", methods=["GET", "POST"])
@login_required
def reminders():
    """Get stock quote."""
    # Redirect if method is GET
    if request.method == "GET":
        return render_template("Reminders.html")

    # else method == POST
    else:
        symbol = request.form.get("symbol")

        if not symbol:
            return apology("please input a symbol")

        # From helpers.py, create a variable to lookup the symbol from the API
        stock = lookup(symbol.upper())

        if stock == None:
            return apology("This symbol does not exist")

        return render_template("quoted.html", symbol = stock["symbol"], price = stock["price"] )


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Ensure Username, password, and confirmation are complete
        if username == "" or password == "" or confirmation == "":
            return apology("missing input", 400)

        rows = db.execute("SELECT * FROM users WHERE username = ?", username)

        # Check if uername exists in the database
        if len(rows) != 0:
            return apology("username already exists", 400)

        # Ensure password and pw_confirm are the same
        if  password != confirmation:
            return apology("password does not match confirmation", 400)

        # Generate a hash of the password for security
        hash = generate_password_hash(password)

        # Add username and hash of password to database
        new_user = db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)

        # Create session to remember user
        session["user_id"] = new_user

        # Redirect user to home index page
        return redirect("/")

    # If POST method is not used, redirect user to register.html
    else:
        return render_template("register.html")


@app.route("/To-Do", methods=["GET", "POST"])
@login_required
def ToDo():
    """Sell shares of stock"""
    if request.method == "GET":
        user_id = session["user_id"]
        user_symbols = db.execute("SELECT symbol FROM transactions WHERE user_id = ? GROUP BY symbol HAVING SUM(shares) > 0", user_id)
        return render_template("To-Do.html", symbols = [row["symbol"] for row in user_symbols])

    else:
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))

        if not symbol:
            return apology("please input a symbol")

        stock = lookup(symbol.upper())

        if stock == None:
            return apology("This symbol does not exist")

        # if the share is less than zero return apology for share not allowed
        if shares < 1:
            return apology("Please input at least one if you would like to sell shares")

        transaction_value = shares * stock["price"]

        user_id = session["user_id"]

        users_cash_db = db.execute("SELECT cash FROM users WHERE id = ?", user_id)

        # Get the first instance of cash from the database for the user
        user_cash = users_cash_db[0]["cash"]

        user_shares = db.execute("SELECT shares FROM transactions WHERE user_id = ? AND symbol = ? GROUP BY symbol", user_id, symbol)

        users_shares = user_shares[0]["shares"]

        if users_shares > shares:
            return apology("You don't have enough shares", 400)

        # Update the user table
        update_cash = user_cash + transaction_value

        # Update the database
        db.execute("UPDATE users SET cash = ? WHERE id = ?", update_cash, user_id)

        # Add a new row to the transaction database with a timestamp
        transaction_date = datetime.datetime.now()

        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, date) VALUES (?, ?, ?, ?, ?)", user_id, stock["symbol"], ((-1)*shares), stock["price"], transaction_date)

        # Display a message using flash
        flash("Stock Sold")

        return redirect("/")



@app.route("/View", methods=["GET", "POST"])
@login_required
def view():
    """Sell shares of stock"""
    if request.method == "GET":
        user_id = session["user_id"]
        user_symbols = db.execute("SELECT symbol FROM transactions WHERE user_id = ? GROUP BY symbol HAVING SUM(shares) > 0", user_id)
        return render_template("View.html", symbols = [row["symbol"] for row in user_symbols])

    else:
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))

        if not symbol:
            return apology("please input a symbol")

        stock = lookup(symbol.upper())

        if stock == None:
            return apology("This symbol does not exist")

        # if the share is less than zero return apology for share not allowed
        if shares < 1:
            return apology("Please input at least one if you would like to sell shares")

        transaction_value = shares * stock["price"]

        user_id = session["user_id"]

        users_cash_db = db.execute("SELECT cash FROM users WHERE id = ?", user_id)

        # Get the first instance of cash from the database for the user
        user_cash = users_cash_db[0]["cash"]

        user_shares = db.execute("SELECT shares FROM transactions WHERE user_id = ? AND symbol = ? GROUP BY symbol", user_id, symbol)

        users_shares = user_shares[0]["shares"]

        if users_shares > shares:
            return apology("You don't have enough shares", 400)

        # Update the user table
        update_cash = user_cash + transaction_value

        # Update the database
        db.execute("UPDATE users SET cash = ? WHERE id = ?", update_cash, user_id)

        # Add a new row to the transaction database with a timestamp
        transaction_date = datetime.datetime.now()

        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, date) VALUES (?, ?, ?, ?, ?)", user_id, stock["symbol"], ((-1)*shares), stock["price"], transaction_date)

        # Display a message using flash
        flash("Stock Sold")

        return redirect("/")
