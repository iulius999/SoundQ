# SoundQ

Discover a world of musical magic with SoundQ, your go-to music companion. SoundQ offers a fusion of features to enhance your musical experience, depending on what type of user you are: admin or listener.

# Features

•  Whether you are an admin or a listener, you can play music your way - SoundQ lets you do that with the ease of a simple click of a button.

•  Managing the melodies isn't a problem either - admins can seamlessly add or remove songs, while listeners can propose songs which would later be accepted or rejected by admins.

•  Explore with simplicity - navigate through the musical universe with SoundQ's search functionality. Your favorite songs and artists are just one search away.

# Layered Architecture Implementation

•  SoundQ was crafted using the versatile Qt framework. Qt, renowned for its cross-platform capabilities and intuitive design, empowers SoundQ with a rich user experience. Its powerful tools and libraries enable the effortless integration of features, making your musical experience straightforward.

•  At the core of SoundQ lies the layered architecture design: Domain, Repository, Service and GUI. Each layer plays a vital role, ensuring that the application runs smoothly and flawlessly.

•  The Domain Layer represents the heart of music - songs.

•  The Repository Layer stores the melodies and connects the application with data sources - text files, in this case.

•  In the Service Layer, algorithms and logic provide sortings, searchings and validations, ensuring the correct communication between data and user interface.

•  The GUI Layer is the cherry on top - aesthetics meet functionality to provide an intuitive interface for users.

# Observer Design Pattern

•  One of the key secrets behind SoundQ's seamless operation is the implementation of the Observer Design Pattern.

•  Through this elegant pattern, changes in one part of the application resonate instantaneously across the entire system, creating a harmonious interplay between windows.
