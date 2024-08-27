@app.route('/complete_note', methods=['POST'])
def complete_note():
    db.execute("INSERT INTO Notes_Archive (user_id, Content, Date, Priority) VALUES (?, ?, ?, ?)", user_id, event, date_string, priority)
    flash('Note archived successfully!')
    return redirect("Notes")




    id = request.form['id']
    user_id = session["user_id"]
    event = request.form.get("Event")
    date_string = (request.form.get("Date"))
    note = request.form.get("Note", type=bool)
    priority = request.form.get("priority")


        db.execute("INSERT INTO Notes_Archive (user_id, Content, Date, Priority) VALUES (?, ?, ?, ?)",
                   note['user_id'], note['Content'], note['Date'], note['Priority'])
        # Delete from notes
        db.execute("DELETE FROM notes WHERE id=?", (id,))






@app.route('/complete_note', methods=['POST'])
def complete_note():
    id = request.form['id']

    user_id = session["user_id"]
    event = db.execute("SELECT * FROM Notes WHERE (id=?)", (id))
    date_string = db.execute("SELECT * FROM Notes WHERE (id=?)", (id))
    priority = db.execute("SELECT * FROM Notes WHERE (id=?)", (id))

    note = db.execute("SELECT * FROM Notes WHERE id=?", (id,))
    if note:
        # Insert into notes_archive
        db.execute("INSERT INTO Notes_Archive (user_id, Content, Date, Priority) VALUES (?, ?, ?, ?)", user_id, event, date_string, priority)

        flash('Note archived successfully!')
    else:
        flash('Note not found!')
    return redirect("Notes")






<h1>Add Event</h1>
    <form action="/Add" method="POST">
        <div class="mb-3">

            <input type="radio" id="Note" name="Note" value="Note">
            <label for="note">Note</label>
            <input type="radio" id="Reminder" name="Reminder" value="Reminder">
            <label for="reminder">Reminder</label>
            <input type="radio" id="To-Do" name="To-Do" value="To-Do">
            <label for="To-Do">To-Do</label>











# THIS SECTION IS FOR HELP - TO BE DELETED
"""
@app.route("/To-Do", methods=["GET", "POST"])
@login_required
def ToDo():
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
"""





        <footer class="mb-5">

            <form action="https://validator.w3.org/check" class="text-center" enctype="multipart/form-data" method="post" target="_blank">
                <input name="doctype" type="hidden" value="HTML5">
                <input name="fragment" type="hidden">
                <input alt="Validate" src="/static/I_heart_validator.png" type="image"> <!-- https://validator.w3.org/ -->
            </form>
            <script>
                document.addEventListener('DOMContentLoaded', function() {
                    // Adapted from https://stackoverflow.com/a/10162353
                    const html = '<!DOCTYPE ' +
                    document.doctype.name +
                    (document.doctype.publicId ? ' PUBLIC "' + document.doctype.publicId + '"' : '') +
                    (!document.doctype.publicId && document.doctype.systemId ? ' SYSTEM' : '') +
                    (document.doctype.systemId ? ' "' + document.doctype.systemId + '"' : '') +
                    '>\n' + document.documentElement.outerHTML;
                    document.querySelector('form[action="https://validator.w3.org/check"] > input[name="fragment"]').value = html;
                });
            </script>
        </footer>


nav .navbar-brand .blue
{
    color: #537fbe;





{% extends "layout.html" %}

{% block title %}
    Apology
{% endblock %}

{% block main %}
    <!-- https://memegen.link/ -->
    <!-- https://knowyourmeme.com/memes/grumpy-cat -->
    <img alt="{{ top }}" class="border img-fluid" src="https://api.memegen.link/images/custom/{{ top | urlencode }}/{{ bottom | urlencode }}.jpg?background=https://i.imgur.com/CsCgN7Ll.png&width=400" title="{{ top }}">


    "/static/styles.css"
    {% endblock %}
