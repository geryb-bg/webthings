hi everyone. So, home automation. Who here has done some home automation. Ok, cool a few people. Well today I'm going to tell you my home automation story. But first, let me introduce myself.

My name is Gergana, but I usually go by Gery because that's easier to pronounce. I recently became a Microsoft MVP and if you would like to know more about me you can follow me on twitter or go and checkout my website for links to some of my projects. I work at BBD in the research and development team. People often ask me what we do in the R&D team, and the plain boring answer is, we facilitate the training of the rest of the staff, we do specialised consulting and of course we do some research. But that's the boring answer, we also do a lot of fun things, such as building meme generators, flying drones with bananas and, my personal favourite, programming astromech droids.

This is pretty much how I started out, almost 4 years ago, I got one of these little robots. I got bored of the app that it came with, so I started finding ways to program it, mostly with javascript. Then I did a few talks on it, and I kind of became known as that robot girl. I continued to play with robots and other electronics, some more successful than others, as you can see from this tweet.

I have hacked quite a few different things, again, mostly with JavaScript. A few months ago, my husband asked me, What about me?

I had been playing with all kinds of robots and electronics, I had written tutorials on how people can automate things in their own houses, but I had not done any of those for our house.

Even, for those of you who may have seen this before, the famous wine button. Is not actually in use in our house. So it was time to do something that was for us.

Our garage doors are weird, sometimes when you push the button for one to close the other opens instead. And sometimes, we just forget to close them. Luckily, we have this neighbour, who is like the area's garage door police. He always posts on the complex whatsapp group when someone has forgotten their garage door open. And even though me and my husband kind of joke about how persistent he is, it is kind of nice that he lets us know. But closing the garage door is not easy, especially if you are already in bed and it's cold outside. So, this is the thing I decided to automate. 

Using Mozilla WebThings. Mozilla web things is an open source implementation of the Web of Things W3C standard. Before we can talk more about this we need to understand what the web of things is. And before we can understand what the web of things is, we need to talk a little bit about that famous buzz word, the internet of things.

IoT has become one of the biggest buzz words of our time, and it's here to stay. It is the idea of being able to connect people, buildings, cars, lights everything from this fancy computer over here to my bottle of water, to one common network in such a way that communication between all of these things is seamless and easy. If we think about the capabilities and power of the computing systems we run, all of this is entirely possible. So why haven't we done this yet, why isn't everything smart, I mean we have a ton of smart things, but we haven't gotten to this futuristic every physical device is connected idea yet. Well this is because we have encountered a few problems with the way in which we are currently building connected smart things.

Fragmentation: A sensor on it's own has very little value, we usually require a number of different sensors in order to get meaningful information from a device. This usually means that we would need to understand a number of different technologies and standards in order to create one internet connected device.

Protocols: MQTT is a widely used protocol standard for IoT devices, however, not all of them use it. There is also AMQP used by Windows IoT, Weave used by Linux and Android Things devices and HomeKit used by devices running on iOS. And these are just the famous ones, there are actually hundreds of different protocols. If we'd like to integrate with a whole range of devices we'd need to understand all of these protocols. 

Connection Methods: WiFi, Bluetooth, NFC, all of these different methods of connecting things to each other. They are all so different, but we still need to understand and deal with all of them in order to be able to achieve the vision that the internet of things promises.

And lastly security: A friend of mine and I were talking a little while ago, and he said to me, "Do you know what the S in IoT stands for?", I said "There's no S in IoT" to which his response was, yes you're correct, there is no security in IoT. Securing your devices is extremely important. Take a look at this headline.

I promise this is not a joke. Cyber criminals actually managed to hack into a casino and steal the personal information of all of the high rollers through the thermostat of the fish tank that sat in the casino's lobby. Security is a difficult part of software in general, for most, it is an after thought. When it comes to IoT, not only is this difficult, but we are also working in unchartered waters. The promise of IoT is amazing, yes, but if we continue in the way we have been going, we are never actually going to get there.

This is where the Web of Things comes in, because, if you think about it, these problems have already been solved on the web. Through many years of experience, we have already developed many standards and protocols for the web. HTTP, for example, brought to the internet a universal way to send images, text and media so that the receiving machine could read and understand the exact message. The Web of Things is that exact same thing, but for devices. Using the protocols of the web, that we know and trust, to connect absolutely anything in the physical world to the World Wide Web. Even security problems on the web have been solved, yes not everybody uses the solutions and there are still a ton of vulnerabilities. But at least we know how to do security on the web.

The formal definition of the web of things is as follows:

"The Web of Things is a refinement of the Internet of Things by integrating smart things not only into the Internet (network), but into the Web Architecture (application)."

It is a high level application protocol designed to optimize interoperability in the Internet of Things. 

In order to get a general understanding we need to talk about the architecture. This architecture is an attempt to organise the protocols and tools of the web in such a way that we can connect anything to the web. It is a layered architecture consisting of 4 layers.

Layer one is the access layer. This layer is responsible for turning any "Thing" into a "Web Thing". What we mean by this is that we are going to create a RESTful API that can communicate with the internet over HTTP as well as communicate with some sort of physical device, such as a garage door. If we think about how we design RESTful APIs we can translate the values of sensors connected to our garage doors to API endpoints. We now have access to the data that our devices are providing in JSON format, meaning that we can use them on the web. But what about real-time data you say, I don't want to have to call an API end point every time I need to check if my garage door is open, I just want to know when it is open. Well, then we can use another protocol from the web, WebSockets. With websockets we can make sure that we get real-time data all of the time.

Ok so now we have our data available on the web either over HTTP or WebSockets. What's next, well we need to make sure that we can find and understand the devices we are exposing. Layer two leverages off of web semantic standards to describe "web things" and the services they provide. In this way devices become searchable in search engines and the data they provide can be used to create user interfaces so that we can interact with them.

Layer three is about sharing. IoT will only truly be a success if all devices are able to share data and information securely. This layer is responsible for defining how this can happen efficiently and safely. Here we can rely on TLS, to encrypt the data that we send between the different devices. We can also start using web authentication methods such as OAuth and OIDC, integrate those into our API and ensure that only the people who are supposed to be seeing the data are seeing it. Again, you can see the security model becomes easier, because we are talking about protocols and tools that we know about and have used before.

Lastly, we need to be able to bring all of these things together, into large scale, enterprise level applications with the fourth layer. In other words, we need to understand the integration of data and services from these Things into an immense ecosystem of web tools such as analytics software and mashup platforms. Here we can use a number of mashup toolkits, JavaScript SDKs, dashboards with programmable widgets or even tools like NODE-RED. 

This architecture is outlined in the W3C specification by the Web of Things Working Group. They are also working on a number of other specifications that will help with the implementations of each of these layers and make it easier for us to connect all of our things to the web. In short, what we want to achieve is a decentralised Internet of Things, by giving every single thing a URL and making it discoverable on the web.

Now we can finally get to what Mozilla WebThings is. So as we said earlier, it is an open source implementation of the Web of Things. It consists of two parts, the gateway and the framework.

The WebThings framework is a collection of reusable software components to help you build your own web thing. This makes them discoverable by the web things gateway or any client that is configured to look for things on the web. Once discovered, the client is able to see details about the web thing and control it over the web. The framework has libraries in a number of different languages including Nodejs, Python, Java, Rust and Arduino. There are also a number of third party libraries for other languages.

Let me show you how you can create a simple web thing device.

//DEMO

The WebThings gateway is a web application that allows you to directly monitor and control your smart home over the web, without a middleman. It has a user interface for controlling your devices, a rules engine to automate them as well as a whole range of add ons with support for existing devices. It being open source also means that if there is an add on you can not find, you can create it yourself and submit a pull request.

You can download the code for the gateway from GitHub and just run it using npm. This is what I did for our house, as we had an old media center computer lying around. If that is not an option for you, you could also get the Raspberry Pi distro and a Pi, the recommended one to use right now is the Raspberry Pi 3. Once your gateway is setup, you can start adding devices. The gateway is also a PWA, which means that you can install it on your phone as an app.

The first time you start up the gateway, you go to localhost:8080 and you fill in the domain name you would like to use together with your email address. This creates an SSL certificate which is stored on the computer you are using and is registered to your email. It also creates a sql lite database which stores all of the information locally. This means that you don't have to have internet in order for all of this stuff to work. Which is an important thing to mention at this point. Even though I keep saying the word web, all of this stuff is capable of working offline. The devices actually connect to the gateway using mDNS, so as long as everything is on the same network it will work, even when your internet dies. You just won't be able to access it from outside the network until your internet comes back.

Once all this is created you are prompted to create a user account. Then you can start adding your devices. Let me show you how this works.

//DEMO

Let's talk about my house and the garage doors. So the demo you just saw is partially used at home, I have a very similar setup with two LEDs. Each LED is connected by a rule, like the ones we created to one of the garage doors. So that if I am about to go to bed and see that one of the lights is on, I know to go close the garage door.

For each garage door we have another ESP32, it is connected to a reed switch that sits on the wall next to the door and has a magnet that sits on the garage door. This way when the garage door opens the reed switch shows that it is open because the magnet has moved away. Lastly I have a relay connected to the actual garage door.

The garage door itself has a relay on it. Closing the connection on the relay on the garage door is the equivalent of pushing the button on your garage door remote. So if it is closed it will open and if it is open it will close. Therefore the relay on the esp32 needs to close for a fraction of a second to complete the circuit and close or open the garage door. Next up I have a short video of my garage doors.

And that's pretty much all I have for now. I am planning on connecting more things, so keep an eye out on my twitter to see when I post more about it if you are interested. I think that with these kinds of standards being taken seriously on the web, we will soon have the internet of things that we deserve.

Thank you. Any questions?