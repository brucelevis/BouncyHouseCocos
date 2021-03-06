import os
import json

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
            print '  Converting %s' % path
            baked_path = baked_path.replace(ext, '.png')
            os.system('convert %s -background transparent -flatten %s' % (path, baked_path))

        if ext in ['.png', '.plist', '.frag']:
            print '  Copying %s' % path
            os.system('cp %s %s' % (path, baked_path))

        if ext == '.json':
            print '  Baking %s' % path
            baked_path = baked_path.replace(ext, '.dna')
            contents = open(path).read()
            data = json.loads(contents)
            f = open(baked_path, 'w')
            f.write(json.dumps(data))
            f.close()
