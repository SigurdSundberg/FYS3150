from numpy import array

sun = 2e30
earth = 6e24
jupiter = 1.9e27
mars = 6.6e23
venus = 4.9e24
saturn = 5.5e26
mercury = 3.3e23
uranus = 8.8e25
neptun = 1.03e26
pluto = 1.31e22


planet_list = array([sun, mercury, venus, earth, mars, jupiter,
                     saturn,  uranus, neptun, pluto])
"Sun mercurys venus earth mars Jupiter satrun uranus neptun pluto"
planet_list = planet_list/sun
with open("../classes/Input/masses.txt", 'w') as o:
    for i in range(len(planet_list)):
        o.write(str(planet_list[i]) + "\n")
