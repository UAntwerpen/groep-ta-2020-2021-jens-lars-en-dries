#define CATCH_CONFIG_MAIN

#include <iostream>
#include "catch.hpp"
#include "../datastructures/Environment.h"
#include "../random/Random.h"

TEST_CASE("Environment Basics") {
    Environment env = Environment(10, 5, 42, true, -0.01, 10, 0.2);
    REQUIRE(env.height == 10);
    REQUIRE(env.width == 5);
    REQUIRE(env.start != env.end);
    REQUIRE(env.states.size() == 50);
}

TEST_CASE("Environment Generation: Deterministic without Obstacles") {
    Environment env = Environment(10, 5, 42, true, -0.01, 10, 0.0);
    SECTION("edge state (0, 0), action: left") {
        MDPState *edge_state = env.get_state_by_coordinates(0, 0);
        std::tuple<MDPState *, float> edge_state_reward(edge_state, env.living_reward);
        // go to the left
        int action = 3;
        std::map<std::tuple<MDPState *, float>, float> state_reward_prob = env.p(edge_state, action);
        // can only be one next state since it's a deterministic environment
        REQUIRE(state_reward_prob.size() == 1);
        // the next state should be the current state
        REQUIRE(state_reward_prob.begin()->first == edge_state_reward);
        // probability should be 100% (deterministic)
        REQUIRE(state_reward_prob.begin()->second == 1.0);
    }

    SECTION("edge state (0, 0), action: up") {
        MDPState *edge_state = env.get_state_by_coordinates(0, 0);
        std::tuple<MDPState *, float> edge_state_reward(edge_state, env.living_reward);
        // go up
        int action = 0;
        std::map<std::tuple<MDPState *, float>, float> state_reward_prob = env.p(edge_state, action);
        // can only be one next state since it's a deterministic environment
        REQUIRE(state_reward_prob.size() == 1);
        // next state should be (0, 1) when going up
        MDPState *next_state = env.get_state_by_coordinates(0, 1);
        std::tuple<MDPState *, float> next_state_reward(next_state, env.living_reward);
        REQUIRE(state_reward_prob.begin()->first == next_state_reward);
        REQUIRE(state_reward_prob.begin()->second == 1.0);
    }

    SECTION("edge state (4, 9), action: up") {
        MDPState *edge_state = env.get_state_by_coordinates(4, 9);
        std::tuple<MDPState *, float> edge_state_reward(edge_state, env.living_reward);
        // go up
        int action = 0;
        std::map<std::tuple<MDPState *, float>, float> state_reward_prob = env.p(edge_state, action);
        // can only be one next state since it's a deterministic environment
        REQUIRE(state_reward_prob.size() == 1);
        // the next state should be the current state
        REQUIRE(state_reward_prob.begin()->first == edge_state_reward);
        // probability should be 100% (deterministic)
        REQUIRE(state_reward_prob.begin()->second == 1.0);
    }


    SECTION("edge state (4, 9), action: down") {
        MDPState *edge_state = env.get_state_by_coordinates(4, 9);
        std::tuple<MDPState *, float> edge_state_reward(edge_state, env.living_reward);
        // go up
        int action = 2;
        std::map<std::tuple<MDPState *, float>, float> state_reward_prob = env.p(edge_state, action);
        // can only be one next state since it's a deterministic environment
        REQUIRE(state_reward_prob.size() == 1);
        // next state should be (0, 1) when going up
        MDPState *next_state = env.get_state_by_coordinates(4, 8);
        std::tuple<MDPState *, float> next_state_reward(next_state, env.living_reward);
        REQUIRE(state_reward_prob.begin()->first == next_state_reward);
        REQUIRE(state_reward_prob.begin()->second == 1.0);
    }

    SECTION("edge state (4, 9), action: right") {
        MDPState *edge_state = env.get_state_by_coordinates(4, 9);
        std::tuple<MDPState *, float> edge_state_reward(edge_state, env.living_reward);
        // go up
        int action = 1;
        std::map<std::tuple<MDPState *, float>, float> state_reward_prob = env.p(edge_state, action);
        // can only be one next state since it's a deterministic environment
        REQUIRE(state_reward_prob.size() == 1);
        // the next state should be the current state
        REQUIRE(state_reward_prob.begin()->first == edge_state_reward);
        // probability should be 100% (deterministic)
        REQUIRE(state_reward_prob.begin()->second == 1.0);
    }
}

TEST_CASE("Environment Generation: Deterministic with Obstacles") {
    Environment env = Environment(5, 2, 42, true, -0.01, 10, 0.2);
    // this seed and configuration leads to (1, 0) and (0, 1) being chosen as obstacles
    // todo this result will change when we implement the path checking!
    SECTION("edge state (0, 0), action: up") {
        MDPState *edge_state = env.get_state_by_coordinates(0, 0);
        std::tuple<MDPState *, float> edge_state_reward(edge_state, env.living_reward);
        // go up
        int action = 0;
        std::map<std::tuple<MDPState *, float>, float> state_reward_prob = env.p(edge_state, action);
        REQUIRE(state_reward_prob.size() == 1);
        REQUIRE(state_reward_prob.begin()->first == edge_state_reward);
        REQUIRE(state_reward_prob.begin()->second == 1.0);
    }

    SECTION("edge state (0, 0), action: right") {
        MDPState *edge_state = env.get_state_by_coordinates(0, 0);
        std::tuple<MDPState *, float> edge_state_reward(edge_state, env.living_reward);
        // go up
        int action = 1;
        std::map<std::tuple<MDPState *, float>, float> state_reward_prob = env.p(edge_state, action);
        REQUIRE(state_reward_prob.size() == 1);
        REQUIRE(state_reward_prob.begin()->first == edge_state_reward);
        REQUIRE(state_reward_prob.begin()->second == 1.0);
    }

    SECTION("edge state (1, 1), action: left") {
        MDPState *edge_state = env.get_state_by_coordinates(1, 1);
        std::tuple<MDPState *, float> edge_state_reward(edge_state, env.living_reward);
        // go down
        int action = 3;
        std::map<std::tuple<MDPState *, float>, float> state_reward_prob = env.p(edge_state, action);
        REQUIRE(state_reward_prob.size() == 1);
        REQUIRE(state_reward_prob.begin()->first == edge_state_reward);
        REQUIRE(state_reward_prob.begin()->second == 1.0);
    }

    SECTION("edge state (1, 1), action: down") {
        MDPState *edge_state = env.get_state_by_coordinates(1, 1);
        std::tuple<MDPState *, float> edge_state_reward(edge_state, env.living_reward);
        // go down
        int action = 2;
        std::map<std::tuple<MDPState *, float>, float> state_reward_prob = env.p(edge_state, action);
        REQUIRE(state_reward_prob.size() == 1);
        REQUIRE(state_reward_prob.begin()->first == edge_state_reward);
        REQUIRE(state_reward_prob.begin()->second == 1.0);
    }

    SECTION("edge state (1, 1), action: up") {
        MDPState *edge_state = env.get_state_by_coordinates(1, 1);
        std::tuple<MDPState *, float> edge_state_reward(edge_state, env.living_reward);
        // go down
        int action = 0;
        std::map<std::tuple<MDPState *, float>, float> state_reward_prob = env.p(edge_state, action);
        REQUIRE(state_reward_prob.size() == 1);
        // next state should be (1, 2) when going up
        MDPState *next_state = env.get_state_by_coordinates(1, 2);
        std::tuple<MDPState *, float> next_state_reward(next_state, env.living_reward);
        REQUIRE(state_reward_prob.begin()->first == next_state_reward);
        REQUIRE(state_reward_prob.begin()->second == 1.0);
    }
}

TEST_CASE("Environment Stepping: Deterministic with Obstacles") {
    Environment env = Environment(5, 5, 42, true, -0.01, 10, 0.2);
    // this seed and configuration leads to (4, 3) as start state
    SECTION("Stepping Run") {
        tuple<MDPState *, float, bool> state_reward_bool;
        // step up once
        state_reward_bool = env.step(0);
        REQUIRE(get<1>(state_reward_bool) == env.living_reward);
        REQUIRE(get<2>(state_reward_bool) == false);
        MDPState * current_state = env.get_state_by_coordinates(4, 4);
        REQUIRE(env.current_state == current_state);
        // step down once
        state_reward_bool = env.step(2);
        REQUIRE(get<1>(state_reward_bool) == env.living_reward);
        REQUIRE(get<2>(state_reward_bool) == false);
        current_state = env.get_state_by_coordinates(4, 3);
        REQUIRE(env.current_state == current_state);
        // go left, up, right
        state_reward_bool = env.step(3);
        REQUIRE(get<1>(state_reward_bool) == env.living_reward);
        REQUIRE(get<2>(state_reward_bool) == false);
        state_reward_bool = env.step(0);
        REQUIRE(get<1>(state_reward_bool) == env.living_reward);
        REQUIRE(get<2>(state_reward_bool) == false);
        state_reward_bool = env.step(1);
        REQUIRE(get<1>(state_reward_bool) == env.living_reward);
        REQUIRE(get<2>(state_reward_bool) == false);
        current_state = env.get_state_by_coordinates(4, 4);
        REQUIRE(env.current_state == current_state);
        // Stepping sequence to the end state
        env.step(3);
        env.step(3);
        env.step(2);
        env.step(2);
        env.step(2);
        state_reward_bool = env.step(3);
        // are in end state: done = true and reward = 10
        REQUIRE(get<1>(state_reward_bool) == env.end_reward);
        REQUIRE(get<2>(state_reward_bool) == true);
    }
}

TEST_CASE("Randomness") {
    Random random(420);
    REQUIRE(random.rand() == 1713004723);
    REQUIRE(random.random() == 1606954614);
    REQUIRE(random.random() == 1705136989);
}