import valve.source
import valve.source.a2s

# 95.211.1.210:27125 208.64.200.65:27015, 208.64.200.39:27011

host = '95.211.1.210'
port = 27125


server_address = (host, port)
with valve.source.a2s.ServerQuerier(server_address) as server:
    info = server.info().get('server_name')
    players = server.players().get('players')
    print(dict(list(players)[0]))

import valve.source.a