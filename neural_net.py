import random
from TicTacToe import Tic
import numpy as np
import tensorflow as tf

LR = 1e-3
initial_games = 10000

def generate_training_data(num_games):
    game = Tic(print_game=False)
    training_data = []
    for g in range(num_games):
        human_moves, comp_moves, winner, board = game.random_game()
        training_data.append([human_moves, comp_moves, winner, board])
    return training_data


def simple_example():

    # Create a tensorflow constant
    const = tf.constant(2.0, name="const")

    # Create tensorflow variables
    b = tf.Variable(2.0, name="b")
    c = tf.Variable(2.0, name="c")

    # Perform operations
    d = tf.add(b, c, name="d")
    e = tf.add(c, const, name="e")
    a = tf.multiply(d, e, name="a")

    # Initialise the variables and graph structure
    init_op = tf.global_variables_initializer()

    # Add ops to save and restore all variables
    saver = tf.train.Saver()

    # Later, launch the model, initialize the variables, do some work, and save the
    # variables to disk
    with tf.Session() as sess:
        # Initialize the variables
        sess.run(init_op)
        # Compute the graph output
        a_out = sess.run(a)
        writer = tf.summary.FileWriter("output", sess.graph)
        writer.close()
        print("Variable A is {}".format(a_out))

# def nn():
#     LR = 0.5
#     epochs = 10
#
#     x = tf.placeholder(tf.float32, [None, 9])
#     y = tf.plceholder(tf.float32, [None, 2])
#
#     # Declare the weights connecting the input to the hidden layer
#     W1 = tf.Variable(tf.random_normal([9, 300], stddev=0.03), name="W1")
#     b1 = tf.Variable(tf.random_normal([300]), name="b1")
#     # Add the weights connecting the hidden layer to the output layer
#     W2 = tf.Variable(tf.random_normal([300, 2], stddev=0.03), name="W2")
#     b2 = tf.Variable(tf.random_normal([2]), name="b2")
#     # Calculate the output of the hidden layer
#     hidden_out = tf.add(tf.matmul(x, W1), b1)
#     hidden_out = tf.nn.relu(hidden_out)
#     # Now calculate the hidden layer output - softmax activation
#     y_ = tf.nn.softmax(tf.add(tf.matmul(hidden_out, W2), b2))
#     y_clipped = tf.clip_by_value(y_, 1e-10, 0.9999999)
#     cross_entropy = -tf.reduce_mean(tf.reduce_sum(y * tf.log(y_clipped)
#                             + (1 - y) * tf.log(1 - y_clipped), axis=1))
#     # Add an optimiser
#     optimiser = tf.train.GradientDescentOptimizer(learning_rate=learning_rate).minimize(cross_entropy)
#
#     # Start the Session
#     with tf.Session as sess:
#         training_data = generate_training_data(1000)
#         # Initialize the variables
#         sess.run(init_op)
#         total_batch = int(len(training_data))
#         for epoch in range(epochs):
#             avg_cost = 0
#             for i in range(total_batch):
#                 batch_x, batch_y =

if __name__ == "__main__":
    # simple_example()
    # training_data = generate_training_data(1000)
    # print(training_data)
