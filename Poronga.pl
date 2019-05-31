totalViaje([],0).
totalViaje([P],TV):- tiempo(P,TV).
totalViaje([V1,V2|L],TV):- tiempo(V1,V2,T1),
						   totalViaje(L,T2),	
						   TV is T1+T2.

tiempo(viaje(X,Y),T):- X < Y,T is Y-X.
tiempo(viaje(X,Y),viaje(X1,Y1),T):- T is (Y-X)+(Y1-X1)+(X1-Y).

validoE(viaje(X,Y)):- X < Y.
validoE(viaje(X,Y),viaje(X1,Y1)):- X < Y, X1 < Y1 ,Y < X1.

valido([]).
valido([V]):- validoE(V).
valido([V1,V2|L]):- validoE(V1,V2),
					valido([V2|L]).

tiempoViaje([],0).
tiempoViaje([P],TV):- tiempo(P,TV).					
tiempoViaje([V1|L],TV):- tiempoViaje([V1],T1),
						 tiempoViaje(L,T2),
						 TV is T1+T2.
						 
tiempoEspera([],0).
tiempoEspera([_],0).
tiempoEspera(L,T):- tiempoViaje(L,A),
					totalViaje(L,B),
					T is B-A.
% 8.
pertenece([],_):-false.
pertenece([X|_],X):-!.
pertenece([_|L],E):- pertenece(L,E).

interseccion([],[],[]):-!.
interseccion([],_,[]):-!.
interseccion(_,[],[]):-!.
interseccion([X|L1],L2,[X|L]):- pertenece(L2,X),
interseccion(L1,L2,L).
interseccion([_|L1],L2,L):- interseccion(L1,L2,L).

esvacio([]).
mismosPuntos(L1,L2):- interseccion(L1,L2,L),esvacio(L).
