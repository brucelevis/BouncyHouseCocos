import os

for root, dirs, files in os.walk('Raw'):
    for filename in files:
        f, ext = os.path.splitext(filename)

        path = os.path.join(root, filename)
        baked_root = root.replace('Raw', 'Baked')
        baked_path = os.path.join(baked_root, filename)

        if '/Frames/' in baked_path:
            #print '  * Skipping %s' % path
            continue

        if not os.path.exists(os.path.dirname(baked_path)):
            os.makedirs(os.path.dirname(baked_path))

        if ext == '.psd':
            baked_path = baked_path.replace(ext, '.png')
            os.system('convert %s -background transparent -flatten %s' % (path, baked_path))
            print '  Converted %s' % path

        if ext in ['.dna', '.png', '.plist']:
            os.system('cp %s %s' % (path, baked_path))
            print '  Copied %s' % path
