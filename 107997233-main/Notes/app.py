from cs50 import SQL
#from datetime import datetime
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required

# Configure application
app = Flask(__name__)

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



@app.route('/delete_note', methods=['POST'])
def delete_note():
    id = request.form['id']
    db.execute("DELETE FROM notes WHERE id=?", (id,))
    flash('Note deleted successfully!')
    return redirect("Notes")

@app.route('/delete_reminder', methods=['POST'])
def delete_reminder():
    id = request.form['id']
    db.execute("DELETE FROM Reminders WHERE id=?", (id,))
    flash('Reminder deleted successfully!')
    return redirect("Reminders")

@app.route('/delete_ToDo', methods=['POST'])
def delete_ToDo():
    id = request.form['id']
    db.execute("DELETE FROM ToDo WHERE id=?", (id,))
    flash('Event deleted successfully!')
    return redirect("To-Do")



@app.route('/complete_note', methods=['POST'])
def complete_note():
    id = request.form['id']
    user_id = session["user_id"]
    note = db.execute("SELECT * FROM Notes WHERE id=?", (id,))[0]
    if note:
        event = note['Content']
        date_string = note['Date']
        time_string = note['Time']
        priority = note['Priority']
        db.execute("INSERT INTO Notes_Archive (user_id, Content, Date, Priority, Time) VALUES (?, ?, ?, ?, ?)", user_id, event, date_string, priority, time_string)
        db.execute("DELETE FROM Notes WHERE id=?", (id,))
        flash('Note archived successfully!')
    else:
        flash('Note not found!')
    return redirect("Notes")

@app.route('/complete_reminder', methods=['POST'])
def complete_reminder():
    id = request.form['id']
    user_id = session["user_id"]
    reminder = db.execute("SELECT * FROM Reminders WHERE id=?", (id,))[0]
    if reminder:
        event = reminder['Content']
        date_string = reminder['Input_Date']
        time_string = reminder['Time']
        priority = reminder['Priority']
        db.execute("INSERT INTO Reminders_Archive (user_id, Content, Input_Date, Priority, Time) VALUES (?, ?, ?, ?, ?)", user_id, event, date_string, priority, time_string)
        db.execute("DELETE FROM Reminders WHERE id=?", (id,))
        flash('Reminder archived successfully!')
    else:
        flash('Reminders not found!')
    return redirect("Reminders")

@app.route('/complete_ToDo', methods=['POST'])
def complete_ToDo():
    id = request.form['id']
    user_id = session["user_id"]
    todo = db.execute("SELECT * FROM ToDo WHERE id=?", (id,))[0]
    if todo:
        event = todo['Content']
        date_string = todo['Input_Date']
        time_string = todo['Time']
        priority = todo['Completion_Date']
        db.execute("INSERT INTO ToDo_Archive (user_id, Content, Input_Date, Completion_Date, Time) VALUES (?, ?, ?, ?, ?)", user_id, event, date_string, priority, time_string)
        db.execute("DELETE FROM ToDo WHERE id=?", (id,))
        flash('Event archived successfully!')
    else:
        flash('Event not found!')
    return redirect("To-Do")



@app.route('/delete_note_archive', methods=['POST'])
def delete_note_archive():
    id = request.form['id']
    db.execute("DELETE FROM Notes_Archive WHERE id=?", (id,))
    flash('Note deleted successfully!')
    return redirect("Notes")

@app.route('/delete_reminder_archive', methods=['POST'])
def delete_reminder_archive():
    id = request.form['id']
    db.execute("DELETE FROM Reminders_Archive WHERE id=?", (id,))
    flash('Reminder deleted successfully!')
    return redirect("Reminders")

@app.route('/delete_ToDo_archive', methods=['POST'])
def delete_ToDo_archive():
    id = request.form['id']
    db.execute("DELETE FROM ToDo_Archive WHERE id=?", (id,))
    flash('Event deleted successfully!')
    return redirect("To-Do")



@app.route("/")
@login_required
def index():
    return render_template("View.html")



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
        return redirect("View")

    # If POST method is not used, redirect user to register.html
    else:
        return render_template("register.html")



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
        return render_template("add.html")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")



@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id and redirect to index page
    session.clear()
    return redirect("/")



@app.route("/Add", methods=["GET", "POST"])
@login_required
def add():
    """Add Note, Reminder or To-Do Event"""

    if request.method == "GET":
        return render_template("add.html")

    else:
        user_id = session["user_id"]
        event = request.form.get("Event")
        date_string = (request.form.get("Date"))
        time_string = (request.form.get("Time"))
        note = request.form.get("Note", type=bool)
        reminder = request.form.get("Reminder", type=bool)
        todo = request.form.get("To-Do", type=bool)
        priority = request.form.get("priority")

        if note:
            db.execute("INSERT INTO Notes (user_id, Content, Date, Priority, Time) VALUES (?, ?, ?, ?, ?)", user_id, event, date_string, priority, time_string)
            flash("Note Added")
            return redirect("Notes")

        if reminder:
            db.execute("INSERT INTO Reminders (user_id, Content, Input_Date, priority, Time) VALUES (?, ?, ?, ?, ?)", user_id, event, date_string, priority, time_string)
            flash("Reminder Added")
            return redirect("Reminders")

        if todo:
            db.execute("INSERT INTO ToDo (user_id, Content, Completion_Date, Time) VALUES (?, ?, ?, ?)", user_id, event, date_string, time_string)
            flash("Task Added")
            return redirect("To-Do")

        return redirect("View")



@app.route("/Notes")
@login_required
def notes():
    user_id = session["user_id"]
    notes_db = db.execute("SELECT * FROM Notes WHERE user_id = ?", user_id)
    notes_archive_db = db.execute("SELECT * FROM Notes_Archive WHERE user_id = ?", user_id)
    return render_template("Notes.html",
                           notes_database = notes_db,
                           notes_archive_database = notes_archive_db)



@app.route("/Reminders", methods=["GET", "POST"])
@login_required
def reminders():
    user_id = session["user_id"]
    reminders_db = db.execute("SELECT * FROM Reminders WHERE user_id = ?", user_id)
    reminders_archive_db = db.execute("SELECT * FROM Reminders_Archive WHERE user_id = ?", user_id)
    return render_template("Reminders.html",
                           reminders_database = reminders_db,
                           reminders_archive_database = reminders_archive_db)



@app.route("/To-Do", methods=["GET", "POST"])
@login_required
def ToDo():
    user_id = session["user_id"]
    todo_db = db.execute("SELECT * FROM ToDo WHERE user_id = ?", user_id)
    todo_archive_db = db.execute("SELECT * FROM ToDo_Archive WHERE user_id = ?", user_id)
    return render_template("To-Do.html",
                           todo_database = todo_db,
                           todo_archive_database = todo_archive_db)



@app.route("/View", methods=["GET", "POST"])
@login_required
def view():
    user_id = session["user_id"]
    notes_db = db.execute("SELECT * FROM Notes WHERE user_id = ?", user_id)
    reminders_db = db.execute("SELECT * FROM Reminders WHERE user_id = ?", user_id)
    todo_db = db.execute("SELECT * FROM ToDo WHERE user_id = ?", user_id)

    return render_template("View.html",
                           notes_database = notes_db,
                           reminders_database = reminders_db,
                           todo_database = todo_db)
