import numpy as np
pi = np.pi

from scipy import ndimage

class Object:
    def __init__(self, x, y, label, parameters):
        self.x = x
        self.y = y
        self.label = label
        #self.theta = theta
        self.parameters = parameters

        
def generateImage(objects, image_w, image_h, snr, a_range=[1,1]):
    image = np.zeros([image_w, image_h])
    bboxes = []
    labels = []
    X, Y = np.meshgrid(np.arange(0, image_w), np.arange(0, image_h))
    for obj in objects:
        x = obj.x
        y = obj.y
        #a = np.random.uniform(i_range[0], i_range[1])
        if obj.label == 'Spot':
            a, sigma = np.array(obj.parameters)
            if a == 0:
                a = np.random.uniform(a_range[0], a_range[1])
            if sigma == 0:
                sigma = np.random.uniform(1.5, 3)
            image = image + a*np.exp(-((X-x)**2+(Y-y)**2)/(2*sigma**2))
            bx = 2*sigma
            by = 2*sigma
            bboxes.append(np.array([[x-bx,y-by],[x+bx,y+by]]))
            labels.append(obj.label)
        if obj.label == 'Ring':
            a, r, sigma = np.array(obj.parameters)
            if a == 0:
                a = np.random.uniform(a_range[0], a_range[1])
            if r == 0:
                r = np.random.uniform(7, 9)
            image = image + a*np.exp(-(np.sqrt((X-x)**2+(Y-y)**2)-r)**2/(2*sigma**2))
            bx = 2*sigma + r
            by = 2*sigma + r
            bboxes.append(np.array([[x-bx,y-by],[x+bx,y+by]]))
            labels.append(obj.label)  
        if obj.label == 'Janus':
            a, r, sigma = np.array(obj.parameters)
            if a == 0:
                a = np.random.uniform(a_range[0], a_range[1])
            if r == 0:
                r = np.random.uniform(8, 16)
            phi = np.random.random()*2*pi
            Xr = x + np.cos(phi)*(X-x) - np.sin(phi)*(Y-y)
            Yr = y + np.sin(phi)*(X-x) + np.cos(phi)*(Y-y)
            angle = np.arccos((Xr-x)/np.sqrt(((Xr-x)**2+(Yr-y)**2)))/2
            image = image + np.cos(angle)**2*a*np.exp(-(np.sqrt((X-x)**2+(Y-y)**2)-r)**2/(2*sigma**2))
            bx = 2*sigma + r
            by = 2*sigma + r
            bboxes.append(np.array([[x-bx,y-by],[x+bx,y+by]]))
            labels.append(obj.label)
        if obj.label == 'Ellipse':
            i0, sigma_x, sigma_y =  np.array(obj.parameters)
            if i0 == 0:
                i0 = np.random.uniform(a_range[0], a_range[1])
            theta = np.random.uniform(0, pi) 
            a = np.cos(theta)**2/(2*sigma_x**2) + np.sin(theta)**2/(2*sigma_y**2)
            b = -np.sin(2*theta)/(4*sigma_x**2) + np.sin(2*theta)/(4*sigma_y**2)
            c = np.sin(theta)**2/(2*sigma_x**2) + np.cos(theta)**2/(2*sigma_y**2)
            image = image + i0*np.exp(-(a*(X-x)**2 + 2*b*(X-x)*(Y-y) + c*(Y-y)**2))
            bx = 2*(np.abs(np.cos(theta))*sigma_x + np.abs(np.sin(theta))*sigma_y)
            by = 2*(np.abs(np.sin(theta))*sigma_x + np.abs(np.cos(theta))*sigma_y)
            bboxes.append(np.array([[x-bx,y-by],[x+bx,y+by]]))
            labels.append(obj.label)
        if obj.label == 'Rod':
            a, length, width, sigma = np.array(obj.parameters)
            if a == 0:
                a = np.random.uniform(a_range[0], a_range[1])
            if length == 0:
                length = np.random.uniform(15, 60)
            im = np.zeros([image_w, image_h])
            im[int(image_w/2-width/2):int(-image_w/2+width/2), int(image_h/2-length/2):int(-image_h/2+length/2)] = 1
            theta = np.random.uniform(0, 2*pi)
            im = ndimage.rotate(im, np.degrees(theta), reshape=False, mode='constant')
            im = ndimage.shift(im, (y-int(image_h/2), x-int(image_w/2)))
            im = ndimage.gaussian_filter(im, sigma)
            im /= im.max()
            image = image + a*im
            sigma_x = length + 2*sigma
            sigma_y = width + 2*sigma
            bx = (np.abs(np.cos(theta))*sigma_x + np.abs(np.sin(theta))*sigma_y)/2
            by = (np.abs(np.sin(theta))*sigma_x + np.abs(np.cos(theta))*sigma_y)/2
            bboxes.append(np.array([[x-bx,y-by],[x+bx,y+by]]))
            labels.append(obj.label)

    # Set the SNR  
    image = image/image.max()
    noise = np.abs(np.random.randn(image_w, image_h))
    noise = noise/np.var(noise)
    if snr == 0: # Random SNR between 1 and 25
        image = np.random.uniform(1, 25)*image + noise # 2, 20   # np.random.randint                
    else:
        image = snr*image + noise                    
    return(bboxes, labels, image) 


def getRandom(frames, n_list, image_w, image_h, distance, offset, label_list, parameters_list):
 
    if not isinstance(n_list, list): 
        n_list = [n_list]
    if not isinstance(label_list, list):
        label_list = [label_list]
    if len(n_list) != len(label_list):
        raise ValueError('The lists must have equal length')
            
    objects = []
    for _ in range(frames):
        positions = np.random.random(2)*(image_w - 2*offset) + offset
        for _ in range(np.sum(n_list)-1):
            min_distance = 0
            while min_distance < distance:
                new_pos = np.random.random(2)*(image_w - 2*offset) + offset
                pos = positions.reshape(int(len(positions)/2), 2)
                d = pos - new_pos
                min_distance = np.sqrt(np.sum(d*d, axis=1)).min()
            positions = np.append(positions, new_pos)
        #if isinstance(labels, list):
        objects.append([Object(x,y, label, parameters) for (x, y), label, parameters in zip(positions.reshape(np.sum(n_list), 2), 
                                                                                            np.repeat(label_list, n_list).tolist(), 
                                                                                            np.repeat(np.array(parameters_list), n_list, axis=0).tolist())])
        #else:
        #    objects_list.append([Object(x,y, labels) for x, y in positions.reshape(n, 2)])      
    return np.array(objects)



def getTrajectories(T, dt, D_list, scale, n_list, image_w, image_h, label_list, parameters_list):
    
    # error handling
    if not isinstance(D_list, list): 
        D_list = [D_list]
    if not isinstance(n_list, list): 
        n_list = [n_list]
    if not isinstance(label_list, list):
        label_list = [label_list]
    length = len(D_list)
    if not all(len(l) == length for l in [n_list, label_list]):
        raise ValueError('The lists must have equal length')
        
    frames = int(T/dt)       
    objects = []
    positions = np.random.uniform((0, 0), (image_w, image_h), size=(np.sum(n_list), 2))
    for _ in range(frames):
        for n, n_cs, D in zip(n_list, np.cumsum(n_list), D_list):
            positions[n_cs-n:n_cs] += np.sqrt(2*D*dt)*np.random.normal(size=(n,2))/scale
        objects.append([Object(x,y, label, parameters) for (x, y), label, parameters in zip(positions, 
                                                                                            np.repeat(label_list, n_list).tolist(), 
                                                                                            np.repeat(np.array(parameters_list), n_list, axis=0).tolist())])
    return np.array(objects)
