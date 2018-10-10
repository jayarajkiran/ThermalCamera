import mysql.connector

global cn, query, cursor
cn = mysql.connector.connect(user='sigrow_read', password='1234',host='database.sigrow.com',database='sigrow')

query = "select par,temp, humid from prod_data1 where remote_id=44628 order by date desc limit 1;"
cursor = cn.cursor()
cursor.execute(query)

for (par,temp,humid) in cursor:
	print("PAR:   ", float(par))
	print("Temp:   ", float(temp))
	print("RH:  ", float(humid))

cursor.close()
cn.close()
            

