/* 
 * Copyright (c) 2013, Giacomo Drago <giacomo@giacomodrago.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *      This product includes cspsolve, a software developed by Giacomo Drago.
 * 4. Neither the name of Giacomo Drago nor the
 *    names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY GIACOMO DRAGO "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL GIACOMO DRAGO BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef CSPSOLVE_H_
#define CSPSOLVE_H_

namespace cspsolve {

template<
    typename Instance,
    typename Variable,
    typename Valid,      // bool(const Instance&, const Variable&)
    typename FirstValue, // void(Instance&, const Variable&)
    typename NextValue,  // bool(Instance&, const Variable&)
    typename Output      // bool(const Instance&)
>
bool solve(Instance& instance,
           Variable firstVariable,
           Variable pastEndVariable,
           Valid valid,
           FirstValue firstValue,
           NextValue nextValue,
           Output output) {

    if (firstVariable == pastEndVariable) { // the range is empty
        return true;
    }
    
    bool solutionFound = false;
    
    Variable variable = firstVariable;
    bool forceInvalid = false;
    
    while (1) {
        
        if (variable == pastEndVariable) { // reached the past-the-end variable of the range
            solutionFound = true;
            // submit solution to "output" callback
            if (output(instance)) { // continue searching
                forceInvalid = true;
                --variable; // go back to the previous variable
            } else { // stop searching
                break;
            }
        } else if (forceInvalid || !valid(instance, variable)) { // invalid partial solution
            forceInvalid = false;
            // try to move to the next value for the variable
            if (!nextValue(instance, variable)) { // if the last value has been reached
                firstValue(instance, variable); // revert to the first value
                if (variable != firstVariable) {
                    forceInvalid = true;
                    --variable; // go back to the previous variable
                } else { // the whole search space has been explored
                    break;
                }
            }
        } else { // move to the next variable
            ++variable;
        }
        
    }
    
    return solutionFound;
    
}

} // namespace cspsolve

#endif // CSPSOLVE_H_
