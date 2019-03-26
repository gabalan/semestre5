from flask import *
from datetime import *

#NE PAS MODIFIER LA LIGNE SUIVANTE
app = Flask(__name__)

#Hello world avec recuperation de parametres
@app.route("/cookies_test", methods=['POST', 'GET'])
def cookies():
    name = ""
    fruit = ""
    if(request.method=='POST'):
        name = request.form['nom']
        fruit = request.form['fruit']
    else:
        name = request.cookies.get("nom")
        fruit = request.cookies.get("fruit")
    
    creation = request.method=='POST'
    resp=make_response(render_template("template_cookies.html", nom=name, fruit=fruit, creation=creation))
    if(creation):
        resp.set_cookie('nom', value=name, expires=datetime.now()+timedelta(days=5))
        resp.set_cookie('fruit', value=fruit, expires=datetime.now()+timedelta(days=5))
        
    return resp

#NE SURTOUT PAS MODIFIER     
if __name__ == "__main__":
   app.run(debug=True)
