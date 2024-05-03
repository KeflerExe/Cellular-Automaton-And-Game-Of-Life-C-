[![LinkedIn][linkedin-shield]][linkedin-url]



<!-- ABOUT THE PROJECT -->
## About The Project

This program developed in C++ implements the game of life by John Horton by using cellular automatons.

The game of life is an example of a cellular automaton designed by the British mathematician
John Horton Conway in 1970. 

We can describe the game of life with the following components:

&emsp;● The cellular space is defined by a two-dimensional lattice, a board where each box is a cell.

&emsp;● The alphabet contains two possible states for each cell: "alive" or "dead."

&emsp;● The neighborhood, called Moore neighborhood, is constituted for each cell by its eight adjacent cells on the board.

&emsp;● The local transition function, which each cell applies to calculate its state in the next generation, depends on its current state and the number of cells with been "alive" in its vicinity. 

The original version of the game uses the transition rule denoted as “23/3”, which consists of:

&emsp;&emsp;○ A cell in the “alive” state with 2 or 3 neighboring cells in the “alive” state continues in a "living" state in the next generation, otherwise it goes to the "dead" state.

&emsp;&emsp;○ A cell in the “dead” state with exactly 3 neighboring cells in the “dead” state "alive" passes to the state "alive" in the next generation, otherwise it remains in a "dead" state.

&emsp;● Boundary conditions: ​​open borders, periodic borders, reflective borders and no borders.

&emsp;&emsp;○ A crosshair is defined that changes size dynamically every time some cell with a “live” state on the edge needs to interact with its neighbors.

The game of life belongs to the category of zero-player game, which means that
Its evolution in successive generations is determined solely by the initial configuration,
and does not require any subsequent data entry.

```diff
@@The operation of the main program is as follows:@@
```

It receives the following arguments via command line:

&emsp;● size <M> <N>, M is the number of rows and N is the number of columns in the
board.

&emsp;● init <file>, (optional) file is a name of the file that contains the values
initials for the state of the board cells.

Performs the evaluation in generations of the game, showing in each generation the
board per screen. 

The user controls the simulation with the following commands
entered by keyboard:

**'x' :** Ends the execution of the program

**'n' :** Calculates and displays the next generation

**'L' :** Calculates and displays the next five generations

**'c':** The 'n' and 'L' commands stop displaying the board status and only display
the population, that is, the number of cells in a "living" state

**'s':** Save the board to a file

<p align="right">(<a href="#readme-top">back to top</a>)</p>



### Built With


* ![C++][C++.js]

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- GETTING STARTED -->
## Getting Started

### Prerequisites

None

### Installation

No installation required :)

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- USAGE EXAMPLES -->
## Usage

1. Download the files
2. Compile with g++
```
g++ cell.cc lattice.cc main_automata.cc
```
4. All ready!

<p align="right">(<a href="#readme-top">back to top</a>)</p>




<!-- LICENSE -->
## License

Distributed under the MIT License.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- CONTACT -->
## Contact

Joel Óscar - josc.margut@gmail.com

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/github_username/repo_name.svg?style=for-the-badge
[contributors-url]: https://github.com/github_username/repo_name/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/github_username/repo_name.svg?style=for-the-badge
[forks-url]: https://github.com/github_username/repo_name/network/members
[stars-shield]: https://img.shields.io/github/stars/github_username/repo_name.svg?style=for-the-badge
[stars-url]: https://github.com/github_username/repo_name/stargazers
[issues-shield]: https://img.shields.io/github/issues/github_username/repo_name.svg?style=for-the-badge
[issues-url]: https://github.com/github_username/repo_name/issues
[license-shield]: https://img.shields.io/github/license/github_username/repo_name.svg?style=for-the-badge
[license-url]: https://github.com/github_username/repo_name/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://www.linkedin.com/in/joel-%C3%B3scar-mart%C3%ADn-guti%C3%A9rrez-578ab8303
[product-screenshot]: images/screenshot.png
[Next.js]: https://img.shields.io/badge/next.js-000000?style=for-the-badge&logo=nextdotjs&logoColor=white
[Next-url]: https://nextjs.org/
[C++.js]: https://img.shields.io/badge/-C++-blue?logo=cplusplus
[React.js]: https://img.shields.io/badge/React-20232A?style=for-the-badge&logo=react&logoColor=61DAFB
[React-url]: https://reactjs.org/
[Vue.js]: https://img.shields.io/badge/Vue.js-35495E?style=for-the-badge&logo=vuedotjs&logoColor=4FC08D
[Vue-url]: https://vuejs.org/
[Angular.io]: https://img.shields.io/badge/Angular-DD0031?style=for-the-badge&logo=angular&logoColor=white
[Angular-url]: https://angular.io/
[Svelte.dev]: https://img.shields.io/badge/Svelte-4A4A55?style=for-the-badge&logo=svelte&logoColor=FF3E00
[Svelte-url]: https://svelte.dev/
[Laravel.com]: https://img.shields.io/badge/Laravel-FF2D20?style=for-the-badge&logo=laravel&logoColor=white
[Laravel-url]: https://laravel.com
[Bootstrap.com]: https://img.shields.io/badge/Bootstrap-563D7C?style=for-the-badge&logo=bootstrap&logoColor=white
[Bootstrap-url]: https://getbootstrap.com
[JQuery.com]: https://img.shields.io/badge/jQuery-0769AD?style=for-the-badge&logo=jquery&logoColor=white
[JQuery-url]: https://jquery.com 
