-module(test_erl).

-record(amap, {akey, bvalue}).
-record(state, {alist = []}).

-behaviour(gen_server).

-export([init/1, start/0, start_link/4, stop/1, handle_call/3, handle_cast/2, handle_info/2, code_change/3, terminate/2]).

-export([test/0, test_replace/1, print/0]).

init(_ABC) ->
	{ok, #state{alist = [#amap{akey = 10, bvalue = a}, #amap{akey = 2, bvalue = b}, #amap{akey = 3, bvalue = c}]}}.
	%%abc.
	
test() ->		
	gen_server:call(?MODULE, {test}).

print() ->		
	gen_server:call(?MODULE, {print}).	
			   
test_replace(#state{alist = AList}) ->
	ATuple = #amap{akey = 100, bvalue = z},
	lists:keyreplace(10, 3, AList, ATuple).

start() ->
	gen_server:start({local, ?MODULE}, ?MODULE, [], []).
	
	
start_link(_Name, _Mod, _Args, _Options) ->
	{ok, self()}.
	
handle_call({test}, _From, State = #state{alist = List}) ->
	NewList = lists:sort(fun(A, B) ->
				A#amap.akey < B#amap.akey end,				
			   List),
	NewState = State#state{alist = NewList},	
	{reply, ok, NewState};
handle_call({print}, _From, State = #state{alist = List}) ->
	io:format("~p", List),		
	{reply, ok, State};		
% handle_call({print}, _From, State = #state{alist = List}) ->
	% lists:foreach(fun(A) -> 
			% io:formart("{k:~p  } ", [A#amap.akey]) end,				
			   % List),			
	% {reply, ok, State};		
handle_call(_Request, _From, _State) ->
	{reply, ok}.
	
handle_cast(_Request, _State) ->
	{noreply, ok}.
	
handle_info(atom_a, State) ->
	io:format("xxxatoma~n"),
	{noreply, State};
handle_info(_, State) ->
	{noreply, State}.

	
code_change(_OldVsn, State, _Extra) ->
    {ok, State}.
	
terminate(_Reason,_State) ->
	ok.
		
stop(_Name) ->
	ok.

