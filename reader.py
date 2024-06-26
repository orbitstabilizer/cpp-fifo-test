FIFO = '/tmp/test_pipe'

with open(FIFO, 'rb') as fifo:
    while True:
        data = fifo.read()
        if len(data) == 0:
            print("Writer closed")
            break
