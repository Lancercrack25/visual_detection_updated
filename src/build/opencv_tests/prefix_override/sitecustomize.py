import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/luis/my_ws/src/install/opencv_tests'
