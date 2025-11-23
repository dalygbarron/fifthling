#include <unistd.h>
#include <stdio.h>
#include <jansson.h>

json_t *root = NULL;
json_t *focus = NULL;




// Nah lets keep the CLI thing, but what if all the event handlers are jacked
// into the output and before we send output to the CLI program, we first send 
// it to everything else that has provided a string with the same prefix, so
// lets say we are sending "set health 5" to the CLI, we might have an
// event listener for "set health" and it just takes the 5 and sets it's health
// meter to 5 or whatever.
// the CLI is a state machine type of deal, so there is no need to state who you
// are setting 5 health on.
// what do we do in the situation where you change levels, though? because in
// that case we need the info from the CLI program. I know, the callback can
// receive both the command executed, and it's response value.
// and first, before anything gets broadcast it can be sent to a validator type
// of thing to make sure there wasn't an error.
// so for an example of the successful instance, lets say we want to change
// levels and then get all of the changed to level's deets, we can run an "n"
// command which means move north, which nothing would be listening to, but then
// we immediately after run the "show" command which everything is listening to
// and causes everything to refresh itself.
// now, lets say there is no level to the north and this causes an error. How
// are we going to handle that? Possibly we could also be looking at input from
// stderr and if we get any we send it to a predefined error callback and don't
// send any info to any handlers, although this does mean that the "show"
// command will still be run immediately after, which isn't a massive problem
// in this case but maybe it would be in another case.
// Maybe we could combine the two into a single command string like "n\nshow"?
// the CLI can be configured to only send output based on the last instruction
// in the set, and listeners can only listen for the last one. So listeners are
// still listening for "show", but they cannot receive it if the preceding "n"
// emits an error.
// Unfortunately I don't think we can use stderr for errors because too many
// libraries shit whatever they want all over it. We can make it flexible by
// having a second kind of listener called a validator that runs first and
// determines whether it's allowed based on the prefix of the response rather
// than the request, it returns a boolean value that says whether or not to
// propagate the event. In our case it would be looking for responses that start
// with "Error:" and it would always return 0 and create a popup window with
// the rest of the error text in it.
// responses shouldn't need to be 1 line, but we need to make sure all of the
// data gets flushed in one go. In theory it might be nice if it was possible
// to return multiple lines of input that could all seperately get sent to
// different places but it would require being very careful with newlines in a
// way that would make CLI usage worse so we are not gonna go there.