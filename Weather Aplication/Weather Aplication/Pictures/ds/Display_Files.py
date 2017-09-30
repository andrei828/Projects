import os
for file in os.listdir():
    print('<BitmapImage x:Key="' + file.split(".")[0] + '" UriSource="./Pictures/ds/' + file + '" />')

