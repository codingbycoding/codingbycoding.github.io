import thread
import time




def testThreadOne():
    print 'testThreadOne begin at: ', time.ctime()
    time.sleep(3)
    print 'testThreadOne end at: ', time.ctime()
    


def testThreadTwo():
    print 'testThreadTwo begin at: ', time.ctime()
    time.sleep(3)
    print 'testThreadTwo end at: ', time.ctime()


def loopMethod(iIndex, nsec, lock):
    print 'loopMethod', iIndex, 'Begin...'
    time.sleep(nsec)
    print 'loopMethod', iIndex, 'End'
    lock.release()

loops = [2, 3]    
def main():
    print 'main():'
    locks = []
    nloop = range(len(loops))
    for i in nloop:
        lock = thread.allocate_lock()
        lock.acquire()
        locks.append(lock)

    for i in nloop:
        thread.start_new_thread(loopMethod, (i, loops[i], locks[i]))

    for i in nloop:
        while locks[i].locked(): pass
        
    # thread.start_new_thread(testThreadOne, ())
    # time.sleep(1)
    # thread.start_new_thread(testThreadTwo, ())
    # time.sleep(7)
    print 'The End. at: ', time.ctime()
    


if __name__ == '__main__':
    print 'run in __main__'
    main()


    
