
# coding: utf-8

# In[1]:

import numpy as np, scipy, scipy.io, matplotlib.pyplot as plt


# In[2]:

train = scipy.io.loadmat( "data/train.mat" )
labels = train[ "train_labels" ]
pre_data = train[ "train_images" ]

data = np.zeros( shape=( 60000, 784 ) )
for n in range( 60000 ):
    for j in range( 28 ):
        for i in range( 28 ):
            data[ n ][ i * 28 + j ] = pre_data[ i ][ j ][ n ]


# In[15]:

def crossvalidation( n, data, labels ):
    num_dim = len( data[ 0 ] )
    num_samples = len( labels )
    
    # Randomize the inputs
    rng_god = np.arange( num_samples )
    np.random.shuffle( rng_god )
    data_shuffled = np.zeros( shape=( num_samples, num_dim ) )
    labels_shuffled = np.zeros( shape=( num_samples ) )
    for i in range( num_samples ):
        data_shuffled[ i ] = data[ rng_god[ i ] ]
        labels_shuffled[ i ] = labels[ rng_god[ i ] ]
        
    # Partition into sets
    if ( num_samples % n ):
        raise Exception( "Unequal size subsets (%d into %d)." % ( num_samples, n ) )
    set_size = num_samples / n
    data_sets = np.zeros( ( n, set_size, num_dim ) )
    labels_sets = np.zeros( ( n, set_size ) )
    for i in range( n ):
        data_sets[ i ] = data_shuffled[ set_size * i : set_size * ( i+1 ) ]
        labels_sets[ i ] = labels_shuffled[ set_size * i : set_size * ( i+1 ) ]

    # Train and score
    score = 0.0
    for i in range( n ):
        classifier = get_classifier( data, labels )
        data_temp = np.concatenate( ( data_sets[ 0 : i ], data_sets[ i : n-1 ] ), 0 )
        data_training = np.zeros( ( set_size * ( n-1 ), num_dim ) )
        for j in range(n - 1):
            for k in range(set_size):
                data_training[ j * set_size + k ] = data_temp[ j ][ k ]
        labels_training = np.concatenate( ( labels_sets[ 0 : i ], labels_sets[ i : n - 1 ] ), 0 ).reshape( set_size * (n - 1) )
        train_classifier( classifier, data_training, labels_training )
        score += score_classifier( classifier, data_sets[ i ], labels_sets[ i ] )
    return score / float( n )


# In[22]:

classifier = 0

if ( classifier == 0 ):
    def get_classifier( data_in, data_out ):
        return [ np.zeros( ( len( data_in[ 0 ] ) ) ) ]
    def train_classifier( classifier, data_in, data_out ):
        for i in range( len( data_out ) ):
            if ( data_out[ i ] >= 2 ):
                continue
            prediction = np.dot( data_in[ i ], classifier[ 0 ] ) > 0
            if ( data_out[ i ] != prediction ):
                sign = 1 if data_out[ i ] > 0 else -1
                classifier[ 0 ] = classifier[ 0 ] + ( data_in[ i ] * sign )
    def score_classifier( classifier, data_in, data_out ):
        import random
        count = 0
        iterations = 0
        for i in range( len( data_out ) ):
            if ( data_out[ i ] >= 2 ):
                continue
            iterations += 1
            prediction = np.dot( data_in[ i ], classifier[ 0 ] ) > 0
            if ( data_out[ i ] == prediction ):
                count += 1
        return float( count ) / iterations

elif ( classifier == 1 ):
    import sklearn
    from sklearn import svm

    def get_classifier( data_in, data_out ):
        return svm.LinearSVC( C=1.0 )
    def train_classifier( classifier, data_in, data_out ):
        classifier.fit( data_in, data_out )
    def score_classifier( classifier, data_in, data_out ):
        return classifier.score( data_in, data_out )
    
elif ( classifier == 2 ):
    import random
    
    def get_classifier( data_in, data_out ):
        return 0
    def train_classifier( classifier, data_in, data_out ):
        return
    def score_classifier( classifier, data_in, data_out ):
        count = 0
        for i in data_out:
            if i == random.randint(0, 9):
                count += 1
        return float( count ) / len( data_out )


# In[23]:

for i in range( 10 ):
    print( crossvalidation( 10, data, labels ) )



