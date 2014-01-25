/* PubNub.h */
/* Copyright (c) 2013 PubNub Inc.
 * http://www.pubnub.com/
 * http://www.pubnub.com/terms
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/** \file
PubNub Client header file
*/

#ifndef PubNub_h
#define PubNub_h


/* TODO: UUID */
/* TODO: secret_key */
/* TODO: cipher_key */


class PubNub {
public:
	/** Init a Pubnub Client context
	 *
	 * Note that the string parameters are not copied; do not
	 * overwrite or free the memory where you stored the keys!
	 * (If you are passing string literals, don't worry about it.)
	 * Note that you should run only a single publish at once.
	 *
	 * @param string publish_key required key to send messages.
	 * @param string subscribe_key required key to receive messages.
	 * @param string origin optional setting for cloud origin.
	 * @return boolean whether begin() was successful. */
	void PubNub(const char *publish_key, const char *subscribe_key, const char *origin = "pubsub.pubnub.com");

	/** Publish
	 *
	 * Send a message (assumed to be well-formed JSON) to a given channel.
	 * This function blocks.
	 *
	 * Examples:
	     p.publish("demo", picojson::value("lala"));
	 * or
	     if (p.publish("demo", picojson::value("lala")) < 0) {
	       blink_error();
	     }
	 *
	 * @param channel required channel name.
	 * @param message required JSON message object.
	 * @param reply optional pointer for passing the returned reply.
	 * @return Zero on success, negative value on error. */
	int publish(const char *channel, picojson::value &message, picojson::value *reply = NULL);

	/** Subscribe
	 *
	 * Listen for a message on a given channel. The function will block
	 * and return when a message arrives. Typically, you will run this
	 * function in a loop to keep listening for messages indefinitely.
	 *
	 * As a reply, you will get a JSON array; you are interested only
	 * in the zeroth element of this array! That element is another
	 * array with actual PubNub messages; the array will frequently
	 * contain a single item, but may also contain multiple messages
	 * or even no messages at all - you must handle all cases.
	 *
	 * Examples:
	     while (1) {
	       picojson::value reply;
	       if (p.subscribe("demo", &reply) < 0) continue;
	       int n_messages = reply.get(0).get<picojson::array>().size();
	       for (int i = 0; i < n_messages; i++)
	         printf("%d: %s\n", i, reply.get(0).get(i).serialize());
	     }
	 *
	 * @param channel required channel name.
	 * @param reply required pointer for passing the returned reply.
	 * @return Zero on success, negative value on error. */
	int subscribe(const char *channel, picojson::value *reply);

	/* TODO: subscribe_multi */

	/** History
	 *
	 * Receive list of the last N messages on the given channel.
	 * This function blocks.
	 *
	 * @param channel required channel name.
	 * @param reply required pointer for passing the returned reply.
	 * @param int limit optional number of messages to retrieve.
	 * @return Zero on success, negative value on error. */
	int history(const char *channel, picojson::value *reply, int limit = 10);

	/* TODO: here_now, time */

	/* TODO: change timeout */

private:
	const char *publish_key, *subscribe_key;
	const char *origin;
};

#endif
